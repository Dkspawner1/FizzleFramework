#!/usr/bin/env fish

set BUILD_TYPE (string lower $argv[1]; or echo "Release")
set BUILD_DIR "cmake-build-$BUILD_TYPE"

echo "🔨 Building FizzleFramework ($BUILD_TYPE)..."

# Clean
if test -d $BUILD_DIR
    echo "🧹 Cleaning old build..."
    rm -rf $BUILD_DIR
end

# Configure
echo "⚙️  Configuring CMake..."
cmake -B $BUILD_DIR -DCMAKE_BUILD_TYPE=$BUILD_TYPE
or exit 1

# Build
echo "🔨 Building..."
cmake --build $BUILD_DIR --config $BUILD_TYPE -j (nproc)
or exit 1

echo "✅ Build complete! Output: $BUILD_DIR"

# For Release, create distribution
if test $BUILD_TYPE = "release"
    set DIST_DIR "FizzleFramework-Release"
    echo "📦 Creating distribution package..."
    mkdir -p $DIST_DIR
    cp $BUILD_DIR/FizzleFramework.exe $DIST_DIR/
    cp -r $BUILD_DIR/assets $DIST_DIR/ 2>/dev/null
    echo "✅ Distribution ready: $DIST_DIR"
end
