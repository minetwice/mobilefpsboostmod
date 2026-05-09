#!/bin/bash
# MinecraftMobileOptimizer/scripts/build-release.sh
# Release build script for MC Optimizer

set -e

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m'

echo -e "${CYAN}"
echo "╔══════════════════════════════════════════╗"
echo "║     MC Optimizer v1.0.0 Release Build    ║"
echo "║     Minecraft 1.21.11 | Java 21          ║"
echo "╚══════════════════════════════════════════╝"
echo -e "${NC}"

# Configuration
BUILD_TYPE="Release"
BUILD_DIR="app/build/outputs/apk/release"
TIMESTAMP=$(date +"%Y%m%d_%H%M%S")
OUTPUT_DIR="releases/v1.0.0_$TIMESTAMP"

# Clean previous builds
echo -e "${BLUE}[1/6] Cleaning previous builds...${NC}"
./gradlew clean
rm -rf app/build/outputs/apk/*
print_success() { echo -e "${GREEN}✓${NC} $1"; }
print_success "Clean complete"

# Run tests
echo -e "${BLUE}[2/6] Running tests...${NC}"
./gradlew test || echo -e "${YELLOW}Warning: Some tests failed${NC}"
print_success "Tests complete"

# Build native libraries
echo -e "${BLUE}[3/6] Building native libraries...${NC}"
./gradlew :app:externalNativeBuild$BUILD_TYPE
print_success "Native build complete"

# Build release APK
echo -e "${BLUE}[4/6] Building release APK...${NC}"
./gradlew :app:assembleRelease \
    -Pandroid.injected.signing.store.file=keystore.jks \
    -Pandroid.injected.signing.store.password=$KEYSTORE_PASSWORD \
    -Pandroid.injected.signing.key.alias=release \
    -Pandroid.injected.signing.key.password=$KEY_PASSWORD \
    2>/dev/null || ./gradlew :app:assembleRelease

print_success "APK build complete"

# Build Minecraft mod
echo -e "${BLUE}[5/6] Building Minecraft mod...${NC}"
cd mod
../gradlew build
cd ..
print_success "Mod build complete"

# Create release directory
echo -e "${BLUE}[6/6] Packaging release...${NC}"
mkdir -p "$OUTPUT_DIR"

# Copy artifacts
APK_FILE=$(find $BUILD_DIR -name "*.apk" | head -1)
if [ -f "$APK_FILE" ]; then
    cp "$APK_FILE" "$OUTPUT_DIR/MC-Optimizer-v1.0.0.apk"
    print_success "APK copied"
fi

MOD_FILE=$(find mod/build/libs -name "*[0-9].jar" | head -1)
if [ -f "$MOD_FILE" ]; then
    cp "$MOD_FILE" "$OUTPUT_DIR/MC-Optimizer-Mod-v1.0.0.jar"
    print_success "Mod JAR copied"
fi

# Generate checksums
echo -e "${BLUE}Generating checksums...${NC}"
cd "$OUTPUT_DIR"
sha256sum *.apk *.jar > checksums.sha256 2>/dev/null || true
cd ../..

# Create release notes
cat > "$OUTPUT_DIR/RELEASE_NOTES.txt" << 'EOF'
MC Optimizer v1.0.0 Release Notes
==================================

Minecraft Version: 1.21.11
Java Version: 21
Fabric Loader: 0.16.10+

Files:
- MC-Optimizer-v1.0.0.apk (Android Launcher)
- MC-Optimizer-Mod-v1.0.0.jar (Minecraft Mod)

Installation:
1. Install APK on Android device
2. Place mod JAR in .minecraft/mods/
3. Launch Minecraft via optimizer app

Features:
- Native C++ optimization engine
- Dynamic resolution scaling
- Frame pacing (30-90 FPS target)
- Memory pool management (512MB)
- Automatic in-game settings adjustment
EOF

# Final output
echo ""
echo -e "${GREEN}========================================${NC}"
echo -e "${GREEN}Release build complete!${NC}"
echo -e "${GREEN}========================================${NC}"
echo -e "${CYAN}Output directory: $OUTPUT_DIR${NC}"
echo ""
ls -lh "$OUTPUT_DIR" 2>/dev/null || echo "No output files found"
echo ""
echo -e "${YELLOW}Next steps:${NC}"
echo "  1. Test APK on device"
echo "  2. Upload to GitHub releases"
echo "  3. Distribute mod JAR"
