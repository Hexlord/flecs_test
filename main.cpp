#include "flecs.h"

using namespace flecs;

struct CComp1 {
  int field;
};
struct CComp2 {
  int field;
};
struct CComp3 {
  int field;
};
int main(int argc, char *argv[]) {
  auto World = flecs::world();
  World.set_threads(1);
  // Removing any of these stops the crash.
  World.component<CComp1>();
  World.component<CComp2>();
  World.component<CComp3>();
  // Removing any of these stops the crash.
  auto Role1 = ecs_new_low_id(World.c_ptr());
  auto Role2 = ecs_new_low_id(World.c_ptr());
  ecs_bulk_desc_t BulkDesc = {};
  // Making this lower stops the crash.
  BulkDesc.count = 1331;
  auto Entities = ecs_bulk_init(World.c_ptr(), &BulkDesc);
  printf("last id: %lu\n", Entities[BulkDesc.count - 1]);
  // < 272 is fine, < 273 leads to crash on ecs fini.
  for (auto Index = 0u; Index < 273; ++Index) {
    auto E = World.entity();
    // 1983 can be changed to 1984 and still crash, not sure about this.
    printf("adding (%lu, %lu) to %lu\n", (unsigned long)Role2, (unsigned long)1983 + Index, E.id());
    E.add(ecs_pair(Role2, 1983 + Index));    
  }
  return 0;
}
