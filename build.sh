BUILD_DIR="build"

if [ ! -d "$BUILD_DIR" ]; then
	echo "Creating build directory!";
	mkdir "$BUILD_DIR";
fi

cd "$BUILD_DIR"

cmake ..
cmake --build .