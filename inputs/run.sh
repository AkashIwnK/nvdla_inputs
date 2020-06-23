INPUT_IMAGE= 

MOD_NAME_PREFIX=hpvm-mod

NVDLA_RUNTIME=nvdla_runtime

OUTPUT=output

./$NVDLA_RUNTIME --loadable $MOD_NAME_PREFIX1.nvdla --image $INPUT_IMAGE --normalize 255 --rawdump
mv $OUTPUT.dimg $OUTPUT1.dimg

./$NVDLA_RUNTIME --loadable $MOD_NAME_PREFIX2.nvdla --image $INPUT_IMAGE --normalize 255 --rawdump
mv $OUTPUT.dimg $OUTPUT2.dimg

./$NVDLA_RUNTIME --loadable $MOD_NAME_PREFIX3.nvdla --image $INPUT_IMAGE --normalize 255 --rawdump
mv $OUTPUT.dimg $OUTPUT3.dimg

./$NVDLA_RUNTIME --loadable $MOD_NAME_PREFIX4.nvdla --image $INPUT_IMAGE --normalize 255 --rawdump
mv $OUTPUT.dimg $OUTPUT4.dimg

./$NVDLA_RUNTIME --loadable $MOD_NAME_PREFIX5.nvdla --image $INPUT_IMAGE --normalize 255 --rawdump
mv $OUTPUT.dimg $OUTPUT5.dimg

./$NVDLA_RUNTIME --loadable $MOD_NAME_PREFIX6.nvdla --image $INPUT_IMAGE --normalize 255 --rawdump
mv $OUTPUT.dimg $OUTPUT6.dimg

./$NVDLA_RUNTIME --loadable $MOD_NAME_PREFIX7.nvdla --image $INPUT_IMAGE --normalize 255 --rawdump
mv $OUTPUT.dimg $OUTPUT7.dimg

./$NVDLA_RUNTIME --loadable $MOD_NAME_PREFIX8.nvdla --image $INPUT_IMAGE --normalize 255 --rawdump
mv $OUTPUT.dimg $OUTPUT8.dimg

./$NVDLA_RUNTIME --loadable $MOD_NAME_PREFIX9.nvdla --image $INPUT_IMAGE --normalize 255 --rawdump
mv $OUTPUT.dimg $OUTPUT9.dimg

./$NVDLA_RUNTIME --loadable $MOD_NAME_PREFIX10.nvdla --image $INPUT_IMAGE --normalize 255 --rawdump
mv $OUTPUT.dimg $OUTPUT10.dimg

./$NVDLA_RUNTIME --loadable $MOD_NAME_PREFIX11.nvdla --image $INPUT_IMAGE --normalize 255 --rawdump
mv $OUTPUT.dimg $OUTPUT11.dimg
