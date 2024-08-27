#include <iostream>

#include "camera.h"
#include "renderer.h"

#include "scene.h"

int main() {
	Renderer renderer;
	Camera camera;
	Scene scene;

	camera.position()[1] =  1.5;
	camera.position()[0] = -1.2;

	std::cout << "Enter renderer samples: ";
	std::cin >> renderer.Settings.Samples;

	renderer.Settings.Depth = 8;

	scene.addMaterial(Material{vec3(0.9)});
	scene.addMaterial(Material{vec3(0.02,0.1, 0.7)});

	scene.add(std::make_shared<Sphere>(vec3(0.0,0.0,0.7), 0.5, 0));
	scene.add(std::make_shared<Sphere>(vec3(1 ,0,-0.1), 0.5, 0));
	scene.add(std::make_shared<Sphere>(vec3(-1,0,-0.1), 0.5, 0));
	scene.add(std::make_shared<Plane>(vec3(0,-.5,0), vec3(0,1,0),1));

	camera.onResize(640,420);
	renderer.onRender(camera, scene);

	scene.clear();
}
