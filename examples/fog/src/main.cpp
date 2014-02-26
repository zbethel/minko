/*
Copyright (c) 2013 Aerys

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "minko/Minko.hpp"
#include "minko/MinkoPNG.hpp"
#include "minko/MinkoSDL.hpp"

using namespace minko;
using namespace minko::component;
using namespace minko::math;

static const std::string TEXTURE_FILENAME = "texture/box.png";
static const std::string EFFECT_FILENAME = "effect/Basic-fog.effect";

static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 600;

int main(int argc, char** argv)
{
	auto canvas = Canvas::create("Minko Example - Fog", WINDOW_WIDTH, WINDOW_HEIGHT);

	auto sceneManager = SceneManager::create(canvas->context());
	
	// setup assets
	sceneManager->assets()->defaultOptions()->resizeSmoothly(true);
	sceneManager->assets()->defaultOptions()->generateMipmaps(true);
	sceneManager->assets()
		->registerParser<file::PNGParser>("png")
		->queue(TEXTURE_FILENAME)
		->queue("effect/Basic-fog.effect");

	sceneManager->assets()->geometry("cube", geometry::CubeGeometry::create(sceneManager->assets()->context()));

	auto root = scene::Node::create("root")
		->addComponent(sceneManager);

	auto mesh = scene::Node::create("mesh")
		->addComponent(Transform::create(Matrix4x4::create()->translation()));

	auto camera = scene::Node::create("camera")
		->addComponent(Renderer::create(0x7f7f7fff))
		->addComponent(Transform::create(
		Matrix4x4::create()->lookAt(Vector3::zero(), Vector3::create(0.f, 0.f, 3.f))
		))
		->addComponent(PerspectiveCamera::create(WINDOW_WIDTH / (float) WINDOW_HEIGHT, (float)PI * 0.25f, .1f, 1000.f));
	root->addChild(camera);

	auto _ = sceneManager->assets()->complete()->connect([=](file::AssetLibrary::Ptr assets)
	{
		auto cubeGeometry = geometry::CubeGeometry::create(sceneManager->assets()->context());

		assets->geometry("cubeGeometry", cubeGeometry);
		
		mesh->addComponent(Surface::create(
			assets->geometry("cubeGeometry"),
			material::BasicMaterial::create()->diffuseMap(assets->texture(TEXTURE_FILENAME)),
			assets->effect("effect/Basic-fog.effect")
			));

		root->addChild(mesh);
	});

	auto resized = canvas->resized()->connect([&](AbstractCanvas::Ptr canvas, uint w, uint h)
	{
		camera->component<PerspectiveCamera>()->aspectRatio((float)w / (float)h);
	});

	auto enterFrame = canvas->enterFrame()->connect([&](Canvas::Ptr canvas, uint time, uint deltaTime)
	{
		mesh->component<Transform>()->matrix()->appendRotationY(.01f);

		sceneManager->nextFrame();
	});

	sceneManager->assets()->load();
	canvas->run();

	return 0;
}

