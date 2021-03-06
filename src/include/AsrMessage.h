#ifndef _ASR_MESSAGE_H_
#define _ASR_MESSAGE_H_

#define  ASRBRIDGE_EVENT_BASE              10000
#define  ASRBRIDGE_CMD_START               (ASRBRIDGE_EVENT_BASE +1)
#define  ASRBRIDGE_CMD_CONFIG              (ASRBRIDGE_EVENT_BASE +2)
#define  ASRBRIDGE_CMD_DATA_CHUNK          (ASRBRIDGE_EVENT_BASE +3)
#define  ASRBRIDGE_CMD_STOP                (ASRBRIDGE_EVENT_BASE +4)

#define L_CB_WORKSTATUS_BASE                20000
#define L_CB_WORKSTATUS_STARTWORKING        (L_CB_WORKSTATUS_BASE+1)
#define L_CB_WORKSTATUS_START               (L_CB_WORKSTATUS_BASE+2)
#define L_CB_WORKSTATUS_END                 (L_CB_WORKSTATUS_BASE+3)
#define L_CB_WORKSTATUS_FLUSHDATA           (L_CB_WORKSTATUS_BASE+4)
#define L_CB_WORKSTATUS_FINISH              (L_CB_WORKSTATUS_BASE+5)
#define L_CB_WORKSTATUS_CHUNK_NLU           (L_CB_WORKSTATUS_BASE+6)
#define L_CB_WORKSTATUS_LONGS_PEECH_END     (L_CB_WORKSTATUS_BASE+7)
#define L_CB_WORKSTATUS_ERROR               (L_CB_WORKSTATUS_BASE+8)
#define L_CB_WORKSTATUS_CANCEL              (L_CB_WORKSTATUS_BASE+9)
#define L_CB_WORKSTATUS_NEW_RECORD_DATA     (L_CB_WORKSTATUS_BASE+10)
#define L_CB_WORKSTATUS_METER_LEVEL         (L_CB_WORKSTATUS_BASE+11)


#endif
