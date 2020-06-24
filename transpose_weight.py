from sys import argv
import numpy as np
from pathlib import Path


eps = 1  # Change this to 1 (or 2) for int8
keras_dtype, nvdla_dtype = np.int8, np.int8


def diff_weights():
    _, keras_in, nvdla_in = argv
    with open(keras_in) as f1:
        keras_data = np.fromfile(f1, dtype=np.float32)
    with open(nvdla_in) as f2:
        nvdla_data = [float(s) for s in f2.read().split(' ') if s]
        nvdla_data = np.array(nvdla_data)
    diff = keras_data - nvdla_data
    diff_selection = diff[np.absolute(diff) > eps]
    n_diff = np.count_nonzero(np.absolute(diff) > eps)
    print(diff_selection, n_diff, len(diff_selection))


# def matmul_diff():
#     x = np.fromfile('max_pooling2d_2_output.bin', dtype=np.float32)
#     flat_w = np.fromfile(argv[1], dtype=np.float16).astype(np.float32)
#     w1 = flat_w.reshape(3136, 1024)
#     w2 = flat_w.reshape(1024, 3136)
#     y1 = w1.T @ x
#     y2 = w2 @ x
#     z1 = np.fromfile('dense_1_output.bin', dtype=np.float32)
#     with open('output7.txt') as f2:
#         nvdla_data = [float(s) for s in f2.read().split(' ') if s]
#         z2 = np.array(nvdla_data)
#     d1 = np.absolute(y1 - z1)
#     d2 = np.absolute(y2 - z2)
#     print(np.count_nonzero(d1 > eps))
#     print(np.count_nonzero(d2 > eps))


def load_transpose_save(weight_path, out_size, in_size):
    w = np.fromfile(weight_path, dtype=nvdla_dtype).reshape(out_size, in_size)
    w.T.tofile(weight_path)


def matmul(weight_path, out_size, in_size, keras_in_path, keras_out_path):
    x = np.fromfile(keras_in_path, dtype=keras_dtype)
    flat_w = np.fromfile(weight_path, dtype=nvdla_dtype).astype(keras_dtype).reshape(in_size, out_size)
    our_y = flat_w @ x
    groundtruth_y = np.fromfile(keras_out_path, dtype=keras_dtype)
    d1 = np.absolute(our_y - groundtruth_y)
    print("# of mismatches: ", np.count_nonzero(d1 > eps))


if __name__ == "__main__":
    prefix = Path(__file__).parent / '../../../hpvm-tensor-rt/model_params/legacy/lenet_nvdla'
    w1 = prefix / 'dense_1_w_int8_quant.bin'
    w2 = prefix / 'dense_2_w_int8_quant.bin'
    w1_in = Path('lenet_int8') / 'max_pooling2d_2_int8_out.bin'
    w1_out = Path('lenet_int8') / 'dense_1_int8_out.bin'
    w2_in = Path('lenet_int8') / 'activation_3_int8_out.bin'
    w2_out = Path('lenet_int8') / 'dense_2_int8_out.bin'
    load_transpose_save(w1, 3136, 1024)
    matmul(w1, 3136, 1024, w1_in, w1_out)
    load_transpose_save(w2, 1024, 10)
    matmul(w2, 1024, 10, w2_in, w2_out)
