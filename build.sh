BUILD_DIR="build"
DLOGGER_DIR="lib/DLogger"

if [ ! -d "$BUILD_DIR" ]; then
	echo "Creating build directory!";
	mkdir "$BUILD_DIR";
fi

if [ ! -d "$DLOGGER_DIR" ]; then
	echo "Cloning DLogger...";
	cd lib
	git clone --depth 1 https://gitlab.com/DerAndereDomenic/dlogger.git 
	cd ..
fi

cd "$BUILD_DIR"

cmake ..
cmake --build .