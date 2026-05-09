#!/bin/bash
# MinecraftMobileOptimizer/scripts/setup-ndk.sh
# NDK setup and verification script

set -e

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}Setting up Android NDK for MC Optimizer...${NC}"

# Default paths
ANDROID_HOME="${ANDROID_HOME:-$HOME/Android/Sdk}"
NDK_VERSION="26.1.10909125"
NDK_PATH="$ANDROID_HOME/ndk/$NDK_VERSION"

# Function to detect OS
detect_os() {
    case "$(uname -s)" in
        Linux*)     echo "Linux";;
        Darwin*)    echo "Mac";;
        CYGWIN*|MINGW*|MSYS*) echo "Windows";;
        *)          echo "Unknown";;
    esac
}

OS=$(detect_os)
echo -e "${BLUE}Detected OS: $OS${NC}"

# Download NDK if not present
download_ndk() {
    if [ -d "$NDK_PATH" ]; then
        echo -e "${GREEN}NDK already installed at: $NDK_PATH${NC}"
        return 0
    fi

    echo -e "${YELLOW}NDK not found. Downloading...${NC}"
    
    mkdir -p "$ANDROID_HOME/ndk"
    cd "$ANDROID_HOME/ndk"
    
    case $OS in
        Linux)
            NDK_ZIP="android-ndk-r26b-linux.zip"
            wget "https://dl.google.com/android/repository/$NDK_ZIP" -O "$NDK_ZIP"
            unzip -q "$NDK_ZIP"
            mv android-ndk-r26b "$NDK_VERSION"
            rm "$NDK_ZIP"
            ;;
        Mac)
            NDK_ZIP="android-ndk-r26b-darwin.zip"
            curl -O "https://dl.google.com/android/repository/$NDK_ZIP"
            unzip -q "$NDK_ZIP"
            mv android-ndk-r26b "$NDK_VERSION"
            rm "$NDK_ZIP"
            ;;
        Windows)
            echo -e "${RED}Please download NDK manually from:${NC}"
            echo "https://developer.android.com/ndk/downloads"
            exit 1
            ;;
    esac
    
    echo -e "${GREEN}NDK downloaded successfully${NC}"
}

# Verify NDK components
verify_ndk() {
    echo -e "${BLUE}Verifying NDK components...${NC}"
    
    local required_files=(
        "$NDK_PATH/build/cmake/android.toolchain.cmake"
        "$NDK_PATH/toolchains/llvm/prebuilt/linux-x86_64/bin/clang++"
        "$NDK_PATH/prebuilt/linux-x86_64/bin/ndk-build"
    )
    
    for file in "${required_files[@]}"; do
        if [ -f "$file" ]; then
            echo -e "${GREEN}✓ $(basename $file)${NC}"
        else
            echo -e "${YELLOW}✗ $(basename $file) not found${NC}"
        fi
    done
}

# Setup environment variables
setup_env() {
    echo -e "${BLUE}Setting up environment variables...${NC}"
    
    # Add to bashrc/zshrc if not present
    local shell_rc="$HOME/.bashrc"
    [ -f "$HOME/.zshrc" ] && shell_rc="$HOME/.zshrc"
    
    if ! grep -q "ANDROID_NDK_HOME" "$shell_rc" 2>/dev/null; then
        echo "" >> "$shell_rc"
        echo "# MC Optimizer NDK Setup" >> "$shell_rc"
        echo "export ANDROID_NDK_HOME=$NDK_PATH" >> "$shell_rc"
        echo "export PATH=\$PATH:\$ANDROID_NDK_HOME/toolchains/llvm/prebuilt/linux-x86_64/bin" >> "$shell_rc"
        echo -e "${GREEN}Added NDK to $shell_rc${NC}"
    fi
    
    export ANDROID_NDK_HOME="$NDK_PATH"
    export PATH="$PATH:$NDK_PATH/toolchains/llvm/prebuilt/linux-x86_64/bin"
}

# Main execution
download_ndk
verify_ndk
setup_env

echo ""
echo -e "${GREEN}========================================${NC}"
echo -e "${GREEN}NDK Setup Complete!${NC}"
echo -e "${GREEN}Version: $NDK_VERSION${NC}"
echo -e "${GREEN}Path: $NDK_PATH${NC}"
echo -e "${GREEN}========================================${NC}"
