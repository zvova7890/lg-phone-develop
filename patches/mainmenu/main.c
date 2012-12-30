#define EVT_CREATE  1
#define EVT_DESTROY 2

#define EVT_RES_ERROR   0
#define EVT_RES_SUCCESS 1

typedef struct {
  int (*evt_handler)(int event_id, int cmd, int subcmd);
  void *base; 
  void *userdata;
}ELF_PARASITE_INFO;

#pragma diag_suppress=Ta035

#pragma swi_number=0x0C
__swi __arm int __elf_unload(ELF_PARASITE_INFO *epi);


__thumb int pxe_event_handler(int event_id, int cmd, int subcmd, ELF_PARASITE_INFO *epi)
{

 switch (event_id)
  {
   case EVT_CREATE:
     {
      if (cmd)
       {
        ELF_PARASITE_INFO *epi_init = (ELF_PARASITE_INFO *)cmd;
        epi->evt_handler = epi_init->evt_handler;
        epi->base        = epi_init->base;
        epi->userdata    = epi_init->userdata;
        
        if (!epi->evt_handler || !epi->base) return EVT_RES_ERROR;
        
        return epi->evt_handler(event_id, cmd, subcmd); 
       } else return EVT_RES_ERROR;
     }
   case EVT_DESTROY:
     {
      if (!epi->evt_handler || !epi->base) return EVT_RES_ERROR;
      epi->evt_handler(event_id, cmd, subcmd);
      __elf_unload(epi);
      return EVT_RES_SUCCESS;
     }
   default:
     {
      if (!epi->evt_handler || !epi->base) return EVT_RES_ERROR;
      else
        return epi->evt_handler(event_id, cmd, subcmd);
     }
  }
}

