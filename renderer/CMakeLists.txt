include_directories(${CMAKE_SOURCE_DIR}/src)
link_directories(${CMAKE_BINARY_DIR}/src)


add_library( renderer
    HitStruct.h
    Vec3D.h Vec3D.cpp
    CoordSys.h CoordSys.cpp
    Camera.h
    PerspectiveCamera.h PerspectiveCamera.cpp
    Ray.h Ray.cpp
    Framebuffer.h Framebuffer.cpp
    Triangle.h Triangle.cpp
    Sphere.h Sphere.cpp
    Shape.h Shape.cpp
    SceneContainer.h SceneContainer.cpp
    Lambertian.h Lambertian.cpp
    Shader.h Shader.cpp
    Light.h Light.cpp 
    pointLight.h 
    BlinnPhong.h BlinnPhong.cpp
    Box.h Box.cpp
    jsonParser.cpp
    MirrorShader.h MirrorShader.cpp
    AABoundingBox.h AABoundingBox.cpp
    BVHNode.h BVHNode.cpp
)

add_executable(raytracer
parseJsonREFACTORED.cpp
)

add_executable(rasterizer
rasterizer.cpp
)

target_link_libraries (raytracer renderer)
target_link_libraries (raytracer sive-util)
target_link_libraries (raytracer ${Boost_PROGRAM_OPTIONS_LIBRARIES})
target_link_libraries (raytracer ${Boost_LIBRARIES})
target_link_libraries (raytracer ${PNG_LIBRARIES})
target_link_libraries (raytracer ${ZLIB_LIBRARIES})

target_link_libraries (rasterizer renderer)
target_link_libraries (rasterizer sive-util)
target_link_libraries (rasterizer ${Boost_PROGRAM_OPTIONS_LIBRARIES})
target_link_libraries (rasterizer ${Boost_LIBRARIES})
target_link_libraries (rasterizer ${PNG_LIBRARIES})
target_link_libraries (rasterizer ${ZLIB_LIBRARIES})












