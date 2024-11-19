# builds the kernel with Jetson Orin Baseboard defconfig
# example:
# export CROSS_COMPILE=aarch64-buildroot-linux-gnu- 
# ./build.sh $PWD/kernel_out

export ARCH=arm64

OUT=$1
echo $OUT
mkdir -p $OUT

make O=$OUT ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE LOCALVERSION="-tegra" p3767_antmicro_job_defconfig
make O=$OUT prepare
make O=$OUT -j$(nproc)
