BUILD_DIR="build"
DLOGGER_DIR="lib/DLogger"

first_build=false

if [ ! -d "$BUILD_DIR" ]; then
	echo "Creating build directory!";
	mkdir "$BUILD_DIR";
	first_build=true
fi

if [ ! -d "$DLOGGER_DIR" ]; then
	echo "Cloning DLogger...";
	cd lib
	git clone --depth 1 https://gitlab.com/DerAndereDomenic/dlogger.git 
	cd dlogger
	rm -r -f .git
	cd ../..
	mv lib/dlogger "${DLOGGER_DIR}"
	first_build=true
fi

cd "$BUILD_DIR"

if [ "$first_build" = true ] ; then
    cmake ..
fi
cmake --build .
