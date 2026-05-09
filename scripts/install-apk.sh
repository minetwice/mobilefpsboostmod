#!/bin/bash
# MinecraftMobileOptimizer/scripts/install-apk.sh
# Install APK to device with logging

set -e

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

APK_PATH="${1:-app/build/outputs/apk/debug/app-debug.apk}"
PACKAGE_NAME="com.mcoptimizer.launcher"

echo -e "${BLUE}MC Optimizer Installer${NC}"
echo "APK: $APK_PATH"
echo ""

# Check device
if ! adb devices | grep -q "device$"; then
    echo -e "${RED}Error: No Android device connected${NC}"
    echo "Please connect a device or start an emulator"
    exit 1
fi

# Get device info
echo -e "${BLUE}Device Info:${NC}"
adb shell getprop ro.product.model
adb shell getprop ro.build.version.release
echo ""

# Uninstall old version
echo -e "${YELLOW}Uninstalling old version...${NC}"
adb uninstall "$PACKAGE_NAME" 2>/dev/null || true

# Install new version
echo -e "${BLUE}Installing APK...${NC}"
adb install -r -d "$APK_PATH"
echo -e "${GREEN}Installation successful!${NC}"

# Launch app
echo -e "${BLUE}Launching app...${NC}"
adb shell am start -n "$PACKAGE_NAME/.launcher.MainActivity"

# Start logcat
echo ""
echo -e "${YELLOW}Starting logcat (Ctrl+C to stop)...${NC}"
adb logcat -c
adb logcat -s "MCOptimizer" "FramePacer" "MemoryPool" "VulkanRenderer" "*:E"
