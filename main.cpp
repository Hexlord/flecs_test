#include "flecs.h"
using namespace flecs;
struct CComp2 {
  int field;
};
struct CSingleton1 {
  int field;
};
int main(int argc, char *argv[]) {
  {
      auto World = flecs::world();  
      World.component<CComp2>().on_remove([&](entity Entity, CComp2 &Comp2){
        auto World = Entity.world();
        auto S = World.get<CSingleton1>(); // fatal: entity.c: 2712: assert: ecs_is_alive(world, entity) INVALID_PARAMETER
        printf("%s\n", S ? "valid" : "invalid");
      });
      World.add<CSingleton1>();
      auto E = World.entity().add<CComp2>();
//      E.destruct(); // this prevents the assert from happening
  }
  return 0;
}
