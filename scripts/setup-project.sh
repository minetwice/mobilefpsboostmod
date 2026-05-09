#!/bin/bash
# MinecraftMobileOptimizer/scripts/setup-project.sh
# Complete project setup script for MC Optimizer v1.0.0

set -e

echo "=========================================="
echo "  MC Optimizer v1.0.0 - Project Setup"
echo "  Minecraft 1.21.11 | Java 21"
echo "=========================================="

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Check if running on Linux/Mac
if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "cygwin" ]]; then
    echo -e "${RED}Error: Please run this in Git Bash or WSL on Windows${NC}"
    exit 1
fi

# Function to print status
print_status() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

# Check Java 21
print_status "Checking Java version..."
if command -v java &> /dev/null; then
    JAVA_VERSION=$(java -version 2>&1 | awk -F '"' '/version/ {print $2}' | cut -d'.' -f1)
    if [[ "$JAVA_VERSION" == "21" ]]; then
        print_success "Java 21 found"
    else
        print_error "Java 21 required but found Java $JAVA_VERSION"
        print_status "Please install Java 21: sudo apt install openjdk-21-jdk"
        exit 1
    fi
else
    print_error "Java not found. Please install Java 21"
    exit 1
fi

# Check Android SDK
print_status "Checking Android SDK..."
if [ -z "$ANDROID_HOME" ]; then
    print_warning "ANDROID_HOME not set"
    print_status "Setting default ANDROID_HOME..."
    export ANDROID_HOME="$HOME/Android/Sdk"
    if [ ! -d "$ANDROID_HOME" ]; then
        print_error "Android SDK not found at $ANDROID_HOME"
        print_status "Please install Android Studio and set ANDROID_HOME"
        exit 1
    fi
fi
print_success "Android SDK found at: $ANDROID_HOME"

# Check NDK
print_status "Checking Android NDK..."
NDK_VERSION="26.1.10909125"
NDK_PATH="$ANDROID_HOME/ndk/$NDK_VERSION"

if [ ! -d "$NDK_PATH" ]; then
    print_warning "NDK $NDK_VERSION not found"
    print_status "Installing NDK via sdkmanager..."
    
    SDK_MANAGER="$ANDROID_HOME/cmdline-tools/latest/bin/sdkmanager"
    if [ ! -f "$SDK_MANAGER" ]; then
        SDK_MANAGER="$ANDROID_HOME/cmdline-tools/bin/sdkmanager"
    fi
    
    if [ -f "$SDK_MANAGER" ]; then
        yes | $SDK_MANAGER "ndk;$NDK_VERSION" --channel=0
    else
        print_error "sdkmanager not found. Please install NDK manually"
        exit 1
    fi
fi

export ANDROID_NDK_HOME="$NDK_PATH"
print_success "NDK found at: $NDK_PATH"

# Create local.properties
print_status "Creating local.properties..."
cat > local.properties << EOF
sdk.dir=$ANDROID_HOME
ndk.dir=$NDK_PATH
EOF
print_success "local.properties created"

# Make gradlew executable
print_status "Setting up Gradle wrapper..."
chmod +x gradlew
chmod +x mod/gradlew 2>/dev/null || true
print_success "Gradle wrapper ready"

# Create necessary directories
print_status "Creating project directories..."
mkdir -p app/src/main/assets
mkdir -p app/src/main/jniLibs/arm64-v8a
mkdir -p app/src/main/jniLibs/armeabi-v7a
mkdir -p mod/build
print_success "Directories created"

# Download dependencies
print_status "Downloading Gradle dependencies..."
./gradlew dependencies --configuration compileClasspath > /dev/null 2>&1 || true
print_success "Dependencies downloaded"

# Verify CMake
print_status "Verifying CMake..."
if [ -f "$NDK_PATH/build/cmake/android.toolchain.cmake" ]; then
    print_success "CMake toolchain found"
else
    print_warning "CMake toolchain not found in NDK"
fi

# Final message
echo ""
echo "=========================================="
print_success "Project setup complete!"
echo ""
echo "Next steps:"
echo "  1. Build Android App: ${YELLOW}./scripts/build-release.sh${NC}"
echo "  2. Build Minecraft Mod: ${YELLOW}cd mod && ../gradlew build${NC}"
echo "  3. Open in Android Studio for development"
echo "=========================================="
