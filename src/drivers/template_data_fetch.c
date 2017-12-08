#include "template_data_fetch.h"
#include "driver_match.h"

void fetch_data_template
(
   void* private_data,
   int index,
   int* template_id,
   void** para_struct
)
{
   struct template_data* private_data_table = private_data;

   *template_id = private_data_table[index].template_id;
   *para_struct = private_data_table[index].para_struct;
}
