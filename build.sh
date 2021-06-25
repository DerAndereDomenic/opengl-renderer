BUILD_DIR="build"

git submodule init
git submodule update

first_build=false

for OPTION in "$@"
do
    case "${OPTION}"
    in
        --setup) ;&
        -s) first_build=true;
		rm -rf "$BUILD_DIR";;
    esac
done

if [ ! -d "$BUILD_DIR" ]; then
	echo "Creating build directory!";
	mkdir "$BUILD_DIR";
	first_build=true
fi

cd "$BUILD_DIR"

if [ "$first_build" = true ] ; then
    cmake .. -Wno-dev -DBUILD_SHARED_LIBS=OFF -DASSIMP_BUILD_ASSIMP_TOOLS=OFF -DASSIMP_BUILD_TESTS=OFF
fi
cmake --build .
