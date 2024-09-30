#include "include/boid.h"
#include "raylib.h"
#include "raymath.h"
#include <vector>

std::vector<Boid*> Boid::boids = std::vector<Boid*>();

Boid::Boid(const Vector2& positionP) :
    position(positionP),
    direction(Vector2{ 0.0f, 0.0f }),
    preyRange(100.0f),
    preyStrength(3.0f),
    predatorRange(100.0f),
    predatorStrength(30.0f),
    alignmentRange(30.0f),
    alignmentStrength(6.0f),
    separationRange(10.0f),
    separationStrength(10.0f),
    cohesionRange(50.0f),
    cohesionStrength(2.0f),
    wallAvoidanceRange(20.0f),
    wallAvoidanceStrength(100.0f),
    steerStrength(0.3f),
    cone(0.2),
    speed(7.0f)
{
    boids.push_back(this);
}

Boid::~Boid() {
    // remover from vector
}

void Boid::render() {
    DrawCircle((int)position.x, (int)position.y, 2.0f, Color { 255, (unsigned char)(255 * direction.x), (unsigned char)(255 * direction.y), 255});
}

void Boid::addSeparation(Vector2& force, Boid *b, const float& range) {
    if (Vector2Distance(b->position, position) <= range) {
        force = Vector2Add(force, Vector2Subtract(position, b->position));
    }
}

void Boid::addCohesion(Vector2& force, Boid *b, const float &range) {
    if (Vector2Distance(b->position, position) <= range) {
        force = Vector2Add(force, Vector2Subtract(b->position, position));
    }
}

void Boid::addAlignment(Vector2& force, Boid* b, const float& range) {
    if (Vector2Distance(b->position, position) <= range) {
        force = Vector2Add(force, b->direction);
    }
}

void Boid::update() {
    Vector2 force{ 0.0f, 0.0f };

    Vector2 alignmentForce{ 0.0f, 0.0f };
    Vector2 separationForce{ 0.0f, 0.0f };
    Vector2 cohesionForce{ 0.0f, 0.0f };

    // calculating neighbours
    for (auto b : boids) {
        if (Vector2DotProduct(Vector2Normalize(Vector2Subtract(b->position, position)), direction) <= cone) {
            addSeparation(separationForce, b, separationRange);
            addAlignment(alignmentForce, b, alignmentRange);
            addCohesion(cohesionForce, b, cohesionRange);
        }
    }

    Vector2 predatorForce{ 0.0f, 0.0f };

    // predator
    Vector2 mousePos = Vector2{ (float)GetMouseX(), (float)GetMouseY() };
    if (Vector2DotProduct(Vector2Normalize(Vector2Subtract(mousePos, position)), direction) <= cone) {
        if (Vector2Distance(mousePos, position) <= predatorRange) {
            if (Vector2Distance(mousePos, position) <= predatorRange) {
                predatorForce = Vector2Add(predatorForce, Vector2Subtract(position, mousePos));
            }
        }
    }

    // Add predator
    force = Vector2Add(force, Vector2Scale(Vector2Normalize(predatorForce), predatorStrength));

    // Add cohesion
    force = Vector2Add(force, Vector2Scale(Vector2Normalize(cohesionForce), cohesionStrength));

    // Add alignment
    force = Vector2Add(force, Vector2Scale(Vector2Normalize(alignmentForce), alignmentStrength));

    // Add separation
    force = Vector2Add(force, Vector2Scale(Vector2Normalize(separationForce), separationStrength));

    // walls
    Vector2 wallForce = { 0.0f, 0.0f };
    if (position.x <= wallAvoidanceRange) {
        wallForce.x += 1.0f;
    }
    if (1000.0f - position.x <= wallAvoidanceRange) {
        wallForce.x += -1.0f;
    }
    if (position.y <= wallAvoidanceRange) {
        wallForce.y += 1.0f;
    }
    if (600.0f - position.y <= wallAvoidanceRange) {
        wallForce.y += -1.0f;
    }

    if (wallForce.x != 0.0f || wallForce.y != 0.0f) {
        force = Vector2Add(force, Vector2Scale(Vector2Normalize(wallForce), wallAvoidanceStrength));
    }

    // apply steering
    force = Vector2Normalize(force);
    direction = Vector2Add(direction, Vector2Scale(force, steerStrength));
    direction = Vector2Normalize(direction);

    position = Vector2Add(position, Vector2Scale(direction, speed));
}