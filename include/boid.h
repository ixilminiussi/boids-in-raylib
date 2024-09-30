#include <vector>
#include "raylib.h"

class Boid {
public:
    Boid(const Vector2& position);
    ~Boid();

    void update();
    void render();

    static std::vector<Boid*> boids;

    Vector2 position;
    Vector2 direction;

private:
    void addSeparation(Vector2& force, Boid *b, const float &range);
    void addAlignment(Vector2& force, Boid *b, const float& range);
    void addCohesion(Vector2& force, Boid *b, const float &range);

    float preyRange;
    float preyStrength;
    float predatorRange;
    float predatorStrength;
    float alignmentRange;
    float alignmentStrength;
    float separationRange;
    float separationStrength;
    float cohesionRange;
    float cohesionStrength;
    float wallAvoidanceRange;
    float wallAvoidanceStrength;
    float steerStrength;
    float cone;
    float speed;
};