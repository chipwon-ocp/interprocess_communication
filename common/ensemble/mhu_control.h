#ifndef MHU_CONTROL_H_
#define MHU_CONTROL_H_

#ifdef __cplusplus
extern "C" {
#endif

#define NUM_MHU                (4)
#define MAXIMUM_TIMEOUT        (0x01000000)

typedef struct payload
{
    char msg[64];
} payload_t;

extern uint32_t services_handle;
extern uint32_t m55_comms_handle;

void MhuInit(void);
void MhuReceiveMsg(void); // msg in 'received_payload' variable.
void MhuSendMsg(void);
void MhuSendUserMsg(char *pusermsg);
void MhuGetPayload(payload_t *ppayload);

#ifdef __cplusplus
}
#endif

#endif // MHU_CONTROL_H_
