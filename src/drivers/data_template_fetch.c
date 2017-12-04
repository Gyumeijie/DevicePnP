#include "data_template_fetch.h"
#include "driver_match.h"

void fetch_data_template
(
   void* private_data,
   int index,
   int* out_template_id,
   void** out_para_struct
)
{
   struct data_template* private_data_table = private_data;

   *out_template_id = private_data_table[index].template_id;
   *out_para_struct = private_data_table[index].para_struct;
}
