#!/bin/bash
# MinecraftMobileOptimizer/scripts/build-debug.sh
# Debug build for development

set -e

GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo -e "${BLUE}Building MC Optimizer DEBUG version...${NC}"

# Build with debug symbols
./gradlew :app:assembleDebug \
    -Pandroid.enableProfileJson=true \
    -Pandroid.native.buildOutput=verbose

echo -e "${GREEN}Debug build complete!${NC}"
echo -e "${YELLOW}APK location: app/build/outputs/apk/debug/${NC}"

# Install to connected device
if adb devices | grep -q "device$"; then
    echo -e "${BLUE}Installing to device...${NC}"
    adb install -r app/build/outputs/apk/debug/app-debug.apk
    echo -e "${GREEN}Installed successfully!${NC}"
else
    echo -e "${YELLOW}No device connected. Install manually.${NC}"
fi
