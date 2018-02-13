#include "Renderer.h"

Renderer::Renderer(GameObject* gameObject) : Component(gameObject) {
	layer = 0;
}

void Renderer::setLayer(int newLayer) {
	layer = newLayer;
}
int Renderer::getLayer() {
    return layer;
}