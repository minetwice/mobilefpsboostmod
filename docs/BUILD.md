# Build Guide - MC Optimizer v1.0.0

## Prerequisites

- JDK 21
- Android Studio Iguana+ 
- Android NDK r26b
- Gradle 8.5+

## Versions

| Component | Version |
|-----------|---------|
| Minecraft | 1.21.11 |
| Java | 21 |
| Fabric Loader | 0.16.10 |
| Fabric API | 0.119.5 |
| Yarn Mappings | 1.21.11+build.1 |

## Build Commands

```bash
# Full build
./gradlew build

# Android only
./gradlew :app:assembleRelease

# Mod only
cd mod && ../gradlew build
