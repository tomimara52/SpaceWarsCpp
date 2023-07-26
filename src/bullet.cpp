#include <SDL2/SDL.h>

#include <cmath>
#include <tuple>

#include "Bullet.h"
#include "CircleCollider.h"
#include "Color.h"
#include "Constants.h"

Bullet::Bullet(double x, double y, double dir, double speed, SDL_Texture *tex, Color color)
    : Entity(x, y, tex, 'b'),
      collider{ CircleCollider{ &pos, Vector2<double>{ 8, 6 }, 6 } },
      dir{ dir }, speed{ speed }, color{ color } {
    currentFrame.x = 23;
    currentFrame.y = 25;
    currentFrame.h = 14;
    currentFrame.w = 18;
}

const CircleCollider* Bullet::getCollider() const {
    return &collider;
}

bool Bullet::collides(Entity* other) const {
    const CircleCollider* otherCollider = other->getCollider();

    if (otherCollider == NULL) return false;

    return collider.collides(otherCollider);
}

void Bullet::simulate(double deltaTime) {
    pos.x += cos(dir) * speed * deltaTime;
    pos.y += sin(dir) * speed * deltaTime;
}

const Color Bullet::getColor() const {
    return color;
}

void Bullet::render(SDL_Renderer* renderer) const {
     SDL_Rect src{ this->getCurrentFrame() };

     Vector2<double> dstVec{ this->getPos() };
     SDL_Rect dst;
     dst.x = dstVec.x;
     dst.y = dstVec.y;
     dst.w = this->getCurrentFrame().w;
     dst.h = this->getCurrentFrame().h;

     double dirRender = (dir * 180 / PI) + 90;
     /*
       dir = ( p_dir + (pi/2) ) * (180/pi)   this transforms radians to degrees
       = (p_dir * (180 / pi)) + 90
     */

     unsigned int r, g, b;
     std::tie(r, g, b) = getHexColor(color);
     
     SDL_SetTextureColorMod(tex, r, g, b);
     SDL_RenderCopyEx(renderer, tex, &src, &dst, dirRender, NULL, SDL_FLIP_NONE);
}

Vector2<double> Bullet::getPosOffsetApplied() const {
    return collider.getPosOffsetApplied();
}
