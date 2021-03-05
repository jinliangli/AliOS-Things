/*******************************************************************************
 * Copyright (c) 2014 IBM Corp.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Ian Craggs - initial API and implementation and/or initial documentation
 *    Xiang Rong - 442039 Add makefile to Embedded C client
 *******************************************************************************/

#ifndef MQTTCONNECT_H_
#define MQTTCONNECT_H_

#if !defined(DLLImport)
    #define DLLImport
#endif
#if !defined(DLLExport)
    #define DLLExport
#endif


#if defined(__CC_ARM)
#ifdef __BIG_ENDIAN
#define MQTT_BIG_ENDIAN 1
#else 
#define MQTT_BIG_ENDIAN 0
#endif
#elif defined(__ICCARM__)
#if (__LITTLE_ENDIAN__ == 0)
#define MQTT_BIG_ENDIAN 1
#else 
#define MQTT_BIG_ENDIAN 0
#endif
#elif defined(__GNUC__)
#if (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define MQTT_BIG_ENDIAN 1
#else 
#define MQTT_BIG_ENDIAN 0
#endif
#endif

#define MQTT_CONN_FLAG_USER_NAME        (0x80)
#define MQTT_CONN_FLAG_PASSWORD         (0x40)
#define MQTT_CONN_FLAG_WILL_RETAIN      (0x20)
#define MQTT_CONN_FLAG_WILL_QOS         (0x18)
#define MQTT_CONN_FLAG_WILL_FLAG        (0x04)
#define MQTT_CONN_FLAG_CLEAN_SESSION    (0x02)

typedef union {
    unsigned char all;  /**< all connect flags */
} MQTTConnectFlags; /**< connect flags byte */

/**
 * Defines the MQTT "Last Will and Testament" (LWT) settings for
 * the connect packet.
 */
typedef struct {
    /** The eyecatcher for this structure.  must be MQTW. */
    char struct_id[4];
    /** The version number of this structure.  Must be 0 */
    int struct_version;
    /** The LWT topic to which the LWT message will be published. */
    MQTTString topicName;
    /** The LWT payload. */
    MQTTString message;
    /**
      * The retained flag for the LWT message (see MQTTAsync_message.retained).
      */
    unsigned char retained;
    /**
      * The quality of service setting for the LWT message (see
      * MQTTAsync_message.qos and @ref qos).
      */
    char qos;
} MQTTPacket_willOptions;


#define MQTTPacket_willOptions_initializer { {'M', 'Q', 'T', 'W'}, 0, {NULL, {0, NULL}}, {NULL, {0, NULL}}, 0, 0 }


typedef struct {
    /** The eyecatcher for this structure.  must be MQTC. */
    char struct_id[4];
    /** The version number of this structure.  Must be 0 */
    int struct_version;
    /** Version of MQTT to be used.  3 = 3.1 4 = 3.1.1
      */
    unsigned char MQTTVersion;
    MQTTString clientID;
    unsigned short keepAliveInterval; /* 单位s */
    unsigned char cleansession;
    unsigned char willFlag;
    MQTTPacket_willOptions will;
    MQTTString username;
    MQTTString password;
} MQTTPacket_connectData;

typedef union {
    unsigned char all;  /**< all connack flags */
#if MQTT_BIG_ENDIAN 
    struct {
        unsigned int sessionpresent : 1;    /**< session present flag */
        unsigned int : 7;                 /**< unused */
    } bits;
#else
    struct {
        unsigned int : 7;                   /**< unused */
        unsigned int sessionpresent : 1;    /**< session present flag */
    } bits;
#endif
} MQTTConnackFlags; /**< connack flags byte */

#define MQTTPacket_connectData_initializer { {'M', 'Q', 'T', 'C'}, 0, 4, {NULL, {0, NULL}}, CONFIG_MQTT_KEEPALIVE_INTERVAL_MIN, 1, 0, \
        MQTTPacket_willOptions_initializer, {NULL, {0, NULL}}, {NULL, {0, NULL}} }

DLLExport int MQTTSerialize_connect(unsigned char *buf, int buflen, MQTTPacket_connectData *options);
DLLExport int MQTTDeserialize_connect(MQTTPacket_connectData *data, unsigned char *buf, int len);

DLLExport int MQTTSerialize_connack(unsigned char *buf, int buflen, unsigned char connack_rc,
                                    unsigned char sessionPresent);
DLLExport int MQTTDeserialize_connack(unsigned char *sessionPresent, unsigned char *connack_rc, unsigned char *buf,
                                      int buflen);

DLLExport int MQTTSerialize_disconnect(unsigned char *buf, int buflen);
DLLExport int MQTTSerialize_pingreq(unsigned char *buf, int buflen);

#endif /* MQTTCONNECT_H_ */
