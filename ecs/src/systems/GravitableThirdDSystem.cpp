#include "Systems/GravitableThirdDSystem.hpp"
#include "Components/Gravitable.hpp"
#include "Components/KeyPressed.hpp"
#include "Components/Position3D.hpp"
#include "ZipperIterator.hpp"

void ecs::systems::GravitableThirdDSystem::operator()(
    std::shared_ptr<Registry> &r,
    std::shared_ptr<IContext> ctx,
    ComponentFactory &factory
)
{
    auto &positions = r->get_components<ecs::component::Position3D>();
    auto &gravitables = r->get_components<ecs::component::Gravitable>();
    auto &keys = r->get_components<ecs::component::KeyPressed>();
    int initialY = INITIAL_Y;
    int targetY = MAX_Y;

    for (auto &&[pos, gravit, key] : custom_zip(positions, gravitables, keys)) {

        if (key->_value == ecs::component::Key::Jump && !gravit->_isJumping && !gravit->_isFalling &&
            pos->_y == initialY) {
            gravit->_isJumping = true;
        }

        if (gravit->_isJumping && pos->_y < targetY) {
            pos->_y += gravit->_gravityFall;
        }

        if (gravit->_isJumping && pos->_y >= targetY) {
            gravit->_isJumping = false;
            gravit->_isFalling = true;
        }

        if (gravit->_isFalling) {
            pos->_y -= gravit->_gravityFall;

            bool onPlatform = false;

            for (size_t i = 0; i < positions.size(); ++i) {
                if (pos->_y <= positions[i]->_y + 1.0 && pos->_y >= positions[i]->_y) {
                    pos->_y = positions[i]->_y + 1.0;
                    gravit->_isFalling = false;
                    gravit->_isJumping = false;
                    key->_value = ecs::component::Key::NoneKey;
                    onPlatform = true;
                    break;
                }
            }

            if (!onPlatform && pos->_y > initialY) {
                pos->_y -= gravit->_gravityFall;
            }
        }

        if (gravit->_isFalling && pos->_y <= initialY) {
            pos->_y = initialY;
            gravit->_isFalling = false;
            key->_value = ecs::component::Key::NoneKey;
        }
    }
}
