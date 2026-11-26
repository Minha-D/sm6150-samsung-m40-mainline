#!/bin/sh
# Turn the pmOS sm7150 config into a first-boot M40 (SM6150 / QCS615) config.
# Usage (from the kernel source tree, so scripts/config exists):
#   cp config-postmarketos-qcom-sm7150.aarch64 config-m40
#   sh m40-kconfig-from-sm7150.sh config-m40
#   cp config-m40 .config && make olddefconfig   # unknown symbols show up here
# Symbol names are the upstream QCS615 ones; verify against YOUR 7.2 tree.
set -e
C="${1:?usage: $0 <config file>}"
S="./scripts/config --file $C"

# --- SoC drivers: replace SM7150 ones with QCS615 (Talos) ones ---
$S -e PINCTRL_QCS615
$S -e QCS_GCC_615
$S -e QCS_DISPCC_615
$S -m QCS_CAMCC_615
$S -m QCS_VIDEOCC_615
$S -m QCS_GPUCC_615
$S -e INTERCONNECT_QCOM_QCS615   # name unverified; check menuconfig

$S -d PINCTRL_SM7150
$S -d PINCTRL_SM7150_LPASS_LPI
$S -d SM_GCC_7150
$S -d SM_DISPCC_7150
$S -d SM_CAMCC_7150
$S -d SM_VIDEOCC_7150
$S -d INTERCONNECT_QCOM_SM7150

# --- Early display / console (SimpleFB on cont_splash, console=tty0) ---
$S -e DRM_SIMPLEDRM
# DSI PHY generation for QCS615 unverified: enable both until you check
# the dsi phy compatible in talos.dtsi
$S -e DRM_MSM_DSI_14NM_PHY
$S -e DRM_MSM_DSI_10NM_PHY

# --- Later stages (modules) ---
$S -m DRM_PANEL_NOVATEK_NT36672A
$S -m TOUCHSCREEN_NOVATEK_NVT_TS

# --- Identity ---
$S --set-str LOCALVERSION "-sm6150"

# --- Optional first-boot suspects (uncomment if needed) ---
# $S -d RANDOMIZE_BASE                       # simplify bring-up
# $S -d ARM_SMMU_DISABLE_BYPASS_BY_DEFAULT   # if splash/DMA faults early
# $S -d ARM64_VA_BITS_52 -e ARM64_VA_BITS_48 # if early boot dies on VA setup

echo "Done. Now run: make olddefconfig  (or pmbootstrap kconfig check)"
