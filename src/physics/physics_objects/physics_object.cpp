#include "physics_object.h"

#include "lib/mathlib.h"

void HinaPE::PhysicsObject::switch_rigidbody_type(HinaPE::RigidBodyType to)
{
    if (physics_object_opt == std::nullopt)
        switch (to)
        {
            case HinaPE::DYNAMIC:
                physics_object_opt = HinaPE::RigidBodyBase<HinaPE::DYNAMIC>();
                break;
            case HinaPE::STATIC:
                physics_object_opt = HinaPE::RigidBodyBase<HinaPE::STATIC>();
                break;
            case HinaPE::KINEMATIC:
                physics_object_opt = HinaPE::RigidBodyBase<HinaPE::KINEMATIC>();
                break;
            default:
                throw std::runtime_error("invalid rigidbody type");
        }
    else
        std::visit(
                overloaded{[&](HinaPE::RigidBodyBase<HinaPE::DYNAMIC> &dyn)
                           {
                               switch (to)
                               {
                                   case HinaPE::NOT_RIGIDBODY:
                                       physics_object_opt = std::nullopt;
                                       break;
                                   case HinaPE::STATIC:
                                       physics_object_opt = HinaPE::switch_rigidbody_type<HinaPE::DYNAMIC, HinaPE::STATIC>(std::get<HinaPE::RigidBodyBase<HinaPE::DYNAMIC>>(physics_object_opt.value()));
                                       break;
                                   case HinaPE::KINEMATIC:
                                       physics_object_opt = HinaPE::switch_rigidbody_type<HinaPE::DYNAMIC, HinaPE::KINEMATIC>(std::get<HinaPE::RigidBodyBase<HinaPE::DYNAMIC>>(physics_object_opt.value()));
                                       break;
                                   default:
                                       throw std::runtime_error("invalid rigidbody type");
                               }
                           },
                           [&](HinaPE::RigidBodyBase<HinaPE::STATIC> &sta)
                           {
                               switch (to)
                               {
                                   case HinaPE::NOT_RIGIDBODY:
                                       physics_object_opt = std::nullopt;
                                       break;
                                   case HinaPE::DYNAMIC:
                                       physics_object_opt = HinaPE::switch_rigidbody_type<HinaPE::STATIC, HinaPE::DYNAMIC>(std::get<HinaPE::RigidBodyBase<HinaPE::STATIC>>(physics_object_opt.value()));
                                       break;
                                   case HinaPE::KINEMATIC:
                                       physics_object_opt = HinaPE::switch_rigidbody_type<HinaPE::STATIC, HinaPE::KINEMATIC>(std::get<HinaPE::RigidBodyBase<HinaPE::STATIC>>(physics_object_opt.value()));
                                       break;
                                   default:
                                       throw std::runtime_error("invalid rigidbody type");
                               }
                           },
                           [&](HinaPE::RigidBodyBase<HinaPE::KINEMATIC> &kin)
                           {
                               switch (to)
                               {
                                   case HinaPE::NOT_RIGIDBODY:
                                       physics_object_opt = std::nullopt;
                                       break;
                                   case HinaPE::DYNAMIC:
                                       physics_object_opt = HinaPE::switch_rigidbody_type<HinaPE::KINEMATIC, HinaPE::DYNAMIC>(std::get<HinaPE::RigidBodyBase<HinaPE::KINEMATIC>>(physics_object_opt.value()));
                                       break;
                                   case HinaPE::STATIC:
                                       physics_object_opt = HinaPE::switch_rigidbody_type<HinaPE::KINEMATIC, HinaPE::STATIC>(std::get<HinaPE::RigidBodyBase<HinaPE::KINEMATIC>>(physics_object_opt.value()));
                                       break;
                                   default:
                                       throw std::runtime_error("invalid rigidbody type");
                               }
                           }},
                physics_object_opt.value());
}

bool HinaPE::PhysicsObject::is_physics_object() const
{
    return physics_object_opt != std::nullopt;
}
