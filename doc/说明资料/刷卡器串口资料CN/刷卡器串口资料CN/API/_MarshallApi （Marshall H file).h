/*                  - Nayax Confidential and Proprietary -
 *
 *  Copyright (C) June 2000, Nayax.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Nayax 
 *  Israel. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 *
 *  Description  : This header file conatain the Marshall API 
 *
 */
 
#ifndef __MARSHALL_API_H__
#define __MARSHALL_API_H__

#ifdef __cplusplus
extern "C" {
#endif
    
/**
* @brief	STM32F2XX - Nayax Amit 
* @brief	VPOS_PORJ - Nayax Vpos 
*/
#ifndef P_STRUCT
  #if defined STM32F2XX
	#include "CM3_wrapper.h"
  #elif defined VPOS_PROJ
    #define P_STRUCT __packed struct 
  #else
	#define P_STRUCT struct
	/* All the structures in this API are 1 byte packed structures !! */
	# pragma pack (1)
  #endif
#endif



					/************************************************/
					/*				  D E F I N E S					*/
					/************************************************/

/**
* @brief	Marshall version
*/
#define MARSHALLAPI_VERSION_STR             "Ver 02.00"
    /*      Ver 1.1:                                               */
    /* - Added MDB sub commands for Multi-Vend(0x82 0x83 0x84)      */
/**
 * @brief	Marshall version
 */
#define MARSHALLAPI_MAJOR_VERSION			2
#define MARSHALLAPI_MINOR_VERSION			0
/**
 * @brief	Amit source address
 */
#define MARSHALLAPI_AMIT_SOURCE_ADDR		0

/**
 * @brief	Max packet length
 */
#define MARSHALLAPI_DEFAULT_PACKET_LENGTH		 512  
/**
 * @brief	Default Rx timeout (waiting for ACK)
 */
#define MARSHALLAPI_DEFAULT_RX_TIMEOUT		     100
/**
 * @brief	Packet overhead (bytes that are used for the protocol management)
 */     
#define MARSHALLAPI_PACKET_OVERHEAD_LENGTH      (MARSHALLAPI_PACKET_HEADR_PACKET_DATA_OFFSET + MARSHALLAPI_PACKET_CRC_SIZE)
/**
 * @brief	Default packet data size
 */
#define MARSHALLAPI_DEFAULT_PACKET_DATA_LENGTH  (MARSHALLAPI_DEFAULT_PACKET_LENGTH - MARSHALLAPI_PACKET_OVERHEAD_LENGTH)    

					/************************************************/
					/*				    E N U M S					*/
					/************************************************/

/**
 * @name 	E_MarshallApi_FuncCode
 * @brief	The Marshall functions code
 */
typedef enum    E_MarshallApi_FuncCode_tag
{
    MARSHALLAPI_CODE_RESPONSE               = 0x00,         /** Response code (ack/nak...) */
    MARSHALLAPI_CODE_RESET                  = 0x01,         /** Reset the Peripheral */
    
    MARSHALLAPI_CODE_FW_INFO                = 0x05,         /** Contains specific FW details */
    MARSHALLAPI_CODE_CONFIG                 = 0x06,         /** Set parameters for communication */
    MARSHALLAPI_CODE_KEEP_ALIVE             = 0x07,         /** Indication that the D200 is still connected */
    MARSHALLAPI_CODE_DISPLAY_MSG            = 0x08,        	/** Displays Message on D200 LCD */
    MARSHALLAPI_CODE_DISPLAY_MSG_STATUS     = 0x09,        	/** Response for displays Message */
	MARSHALLAPI_CODE_TRANSFER_DATA			= 0x0A,        	/** Transfer specific data  */
	MARSHALLAPI_CODE_STATUS					= 0x0B,        	/** Status message */
    MARSHALLAPI_CODE_GET_TIME				= 0x0C,        	/** Get Time */
    MARSHALLAPI_CODE_TIME				    = 0x0D,         /** Time */
    MARSHALLAPI_CODE_SET_PARAMETER			= 0x0E,         /** Set peripheral parameter */
    
    MARSHALLAPI_CODE_MRDR_COMMAND			= 0x10,         /** MRDR command */
    
    MARSHALLAPI_CODE_MODEM_STATUS           = 0x20,         /** Modem status */
    MARSHALLAPI_CODE_OPEN_SOCKET            = 0x21,         /** Open a socket for comm. with a server */
    MARSHALLAPI_CODE_CLOSE_SOCKET           = 0x22,         /** Close socket opened for comm. with server */
    MARSHALLAPI_CODE_SEND_DATA              = 0x23,         /** Send Data to server */
    MARSHALLAPI_CODE_RCV_DATA               = 0x24,         /** data received from server */
    MARSHALLAPI_CODE_RX_CONTROL             = 0x25,         /** Modem Rx control */
    
    MARSHALLAPI_CODE_TRACE                  = 0x30,         /** Send Trace parameters to Amit */
    MARSHALLAPI_CODE_ALERT                  = 0x31,         /** Send Alert to Amit */   
    
    MARSHALLAPI_CODE_GET_FILE_VERSION		= 0x32,        	/** Get file version by file ID */
    MARSHALLAPI_CODE_FILE_VERSION		    = 0x33,         /** File version */
    MARSHALLAPI_CODE_SEND_FILE  		    = 0x34,         /** Send file / file header */
    MARSHALLAPI_CODE_CHECK_FILE_CRC 	    = 0x35,         /** Check file CRC16 */
    MARSHALLAPI_CODE_FW_UPDATE  		    = 0x36,         /** FW (POS) update */
            
    MARSHALLAPI_CODE_MDB_CMD                = 0x80,         /** Retrieve received Data message from server */ 
    
    MARSHALLAPI_CODE_PP_SET_EVENT           = 0x90,         /** Pin pad - Set event type to be activated on D200 */
    MARSHALLAPI_CODE_PP_EVENT               = 0x91,       	/** Pin pad - Event type that occurred on PINPad and its specific data */
    MARSHALLAPI_CODE_PP_TRANS_REQUEST       = 0x92,       	/** Pin pad - Provide to D200 Transaction’s parameters */
    MARSHALLAPI_CODE_PP_DISP_CONFIRM        = 0x93,         /** Pin pad - Indication whether the product was dispensed correctly or not */
    MARSHALLAPI_CODE_PP_TRANS_CANCEL        = 0x94,         /** Pin pad - Two-way command in order to cancel a transaction */
    MARSHALLAPI_CODE_PP_END_TRANS           = 0x95,         /** Pin pad - Indicates end of transaction */    

    MARSHALLAPI_CODE_MAX,

} E_MarshallApi_FuncCode;



					/************************************************/
					/*			P A C K E T    H E A D E R  	    */
					/************************************************/

/**
 * @name 	E_MarshallApi_FuncCode
 * @brief	The Marshall header structure
 */
typedef P_STRUCT S_MarshallApi_PacketHeader_tag
{
	uint16_t	PacketLength;			                    /** Length of Packet Message (It include the CRC but exclude itself)*/
	uint8_t		PacketOptions;			                    /** Packet Options bitmap */
	uint8_t		PacketId;				                    /** Packet ID - Running Identifier */
	uint8_t		Source;					                    /** Source of Packet */
	uint8_t		SourceLsb;				                    /** LSB Serial Number of Source */
	uint8_t		Dest;					                    /** Destination of Packet */
	uint8_t		DestLsb;				                    /** LSB Serial Number of Destination */
	uint8_t		FuncCode;				                    /** Specific Code of Function */

}S_MarshallApi_PacketHeader;

/**
 * @brief	Packet length size
 */
#define MARSHALLAPI_PACKET_LENGTH_SIZE		                2


/**
 * @brief 	Packet header members offset
 */
#define MARSHALLAPI_PACKET_HEADR_PACKET_LENGTH_OFFSET		0
#define MARSHALLAPI_PACKET_HEADR_PACKET_OPTIONS_OFFSET		2
#define MARSHALLAPI_PACKET_HEADR_PACKET_ID_OFFSET			3
#define MARSHALLAPI_PACKET_HEADR_PACKET_SRC_ADDR_OFFSET		4
#define MARSHALLAPI_PACKET_HEADR_PACKET_SRC_LSB_OFFSET		5
#define MARSHALLAPI_PACKET_HEADR_PACKET_DST_ADDR_OFFSET		6
#define MARSHALLAPI_PACKET_HEADR_PACKET_DST_LSB_OFFSET		7
#define MARSHALLAPI_PACKET_HEADR_PACKET_FUNC_CODE_OFFSET	8
#define MARSHALLAPI_PACKET_HEADR_PACKET_DATA_OFFSET			9


/**
 * @brief	Packet options
 */
#define	MARSHALLAPI_OPTIONS_ACK_REQUESTED_OFFSET		    0
#define	MARSHALLAPI_OPTIONS_ACK_REQUESTED_MASK			    0x01
#define	MARSHALLAPI_OPTIONS_ACK_NOT_REQUESTED			    0
#define	MARSHALLAPI_OPTIONS_ACK_REQUESTED				    0x1

#define	MARSHALLAPI_OPTIONS_PACKET_ENCRYPTED_OFFSET		    1
#define	MARSHALLAPI_OPTIONS_PACKET_ENCRYPTED_MASK		    0x02
#define	MARSHALLAPI_OPTIONS_PACKET_NOT_ENCRYPTED		    0
#define	MARSHALLAPI_OPTIONS_PACKET_ENCRYPTED			    1

#define	MARSHALLAPI_OPTIONS_RETRY_NUMBER_OFFSET			    2
#define	MARSHALLAPI_OPTIONS_RETRY_NUMBER_MASK			    0x0C

#define	MARSHALLAPI_OPTIONS_LAST_PACKET_DATA_OFFSET		    4
#define	MARSHALLAPI_OPTIONS_LAST_PACKET_DATA_MASK		    0x10
#define	MARSHALLAPI_OPTIONS_LAST_PACKET_DATA_LAST		    0
#define	MARSHALLAPI_OPTIONS_LAST_PACKET_DATA_NOT_LAST	    1

#define	MARSHALLAPI_OPTIONS_RFU_OFFSET					    5
#define	MARSHALLAPI_OPTIONS_RFU_MASK					    0xE0

					/************************************************/
					/*			P A C K E T    F O O T E R  	    */
					/************************************************/

/**
 * @brief	Packet length size
 */
#define MARSHALLAPI_PACKET_CRC_SIZE		                    2

/**
 * @name 	S_MarshallApi_PacketFooter
 * @brief	The Marshall packet structure
 */
typedef P_STRUCT S_MarshallApi_PacketFooter_tag
{
	uint16_t	Crc;					/** Packet CRC signature */

}S_MarshallApi_PacketFooter;

					/************************************************/
					/*				 R E S P O N S E    	   	 	*/
					/************************************************/

/**
 * @brief	Response data size
 */
#define MARSHALLAPI_RESPONSE_CMD_DATA_SIZE				    1

/**
 * @name 	E_MarshallApi_ResponseVal
 * @brief	Function - Response
 */
typedef enum E_MarshallApi_ResponseVal_tag
{
	MARSHALLAPI_RESPONSE_VAL_ACK 						    = 0,
	MARSHALLAPI_RESPONSE_VAL_CRC_ERROR 					    = 1,
	MARSHALLAPI_RESPONSE_VAL_WRONG_DST_ADDR 			    = 2,
	MARSHALLAPI_RESPONSE_VAL_NON_CONSECUTIVE_PACKET_ID 	    = 3,
	MARSHALLAPI_RESPONSE_VAL_NONE_REGISTERED_SRC	 	    = 4,
	MARSHALLAPI_RESPONSE_VAL_UNEXPECTED_ERROR 			    = 10,

	MARSHALLAPI_RESPONSE_VAL_MAX,

}E_MarshallApi_ResponseVal;

					/************************************************/
					/*		    F I R M W A R E   I N F O   		*/
					/************************************************/

/**
 * @name 	S_MarshallApi_FirmInfoParams
 * @brief	The Firm Info structure
 */
typedef P_STRUCT S_MarshallApi_FirmInfoParams_tag
{

	uint8_t			ProtocolVerMajor;					                /** Protocol version (Major) 			*/
	uint8_t			ProtocolVerMinor;					                /** Protocol version (Minor) 			*/
	uint8_t			PeripheralType;						                /** Peripheral type			 			*/
	uint8_t			PeripheralSubType;					                /** Peripheral sub type		 			*/
	uint16_t		PeripheralCapabilities;			                    /** Peripheral Capabilities	 			*/
	uint8_t			PeripheralModel[20];				                /** Peripheral Model	 				*/
	uint8_t			PeripheralSerialNum[20];			                /** Peripheral SerialNum 				*/
	uint8_t			PeripheralAppSwVer[20];				                /** Peripheral Application SW Version	*/

}S_MarshallApi_FirmInfoParams;

/**
 * @name 	E_MarshallApi_FirmInfoType
 * @brief	Firmware info - type
 */
typedef enum E_MarshallApi_FirmInfoType_tag
{
    MARSHALLAPI_INFO_TYPE_RESERVED_1                        = 0,        /** Reserved                            */
    MARSHALLAPI_INFO_TYPE_RESERVED_2                        = 1,        /** Reserved                            */
    MARSHALLAPI_INFO_TYPE_CRD_RDR                           = 2,        /** Card Readers                        */
    MARSHALLAPI_INFO_TYPE_PHOTO_BOOTH                       = 3,        /** Photo Booth                         */
    MARSHALLAPI_INFO_TYPE_GENERAL							= 4,        /** General								*/
    MARSHALLAPI_INFO_TYPE_BEVERAGE_MACHINE                  = 5,        /** Beverage machines                   */
    MARSHALLAPI_INFO_TYPE_WATER_FILLING_MACHINE             = 6,        /** Water filling machine               */
    MARSHALLAPI_INFO_TYPE_LOCKER                            = 7,        /** Locker                              */
    MARSHALLAPI_INFO_TYPE_RETAIL                            = 8,        /** Retail                              */
    MARSHALLAPI_INFO_TYPE_LAUNDRY_MACHINE                   = 9,        /** Laundry machine                     */
    MARSHALLAPI_INFO_TYPE_E_MONEY                           = 10,       /** E money                             */
	MARSHALLAPI_INFO_TYPE_EV_CHARGER						= 11,       /** EV (electric vehicle) Charger       */
    MARSHALLAPI_INFO_TYPE_MAX,

} E_MarshallApi_FirmInfoType;

/**
 * @name 	E_MarshallApi_InfoCardRdrSubType
 * @brief	Firmware info - Nayax card reader sub types
 */
typedef enum E_MarshallApi_CardRdrSubType_tag
{
    MARSHALLAPI_INFO_CARD_RDR_SUB_TYPE_RESERVED             = 0,   
    MARSHALLAPI_INFO_CARD_RDR_SUB_TYPE_1                    = 1,   
    MARSHALLAPI_INFO_CARD_RDR_SUB_TYPE_2                    = 2,   

    MARSHALLAPI_INFO_CARD_RDR_SUB_TYPE_MAX,

} E_MarshallApi_InfoNayaxRdrSubType;

/**
 * @name 	E_MarshallApi_InfoPhotoBoothSubType
 * @brief	Firmware info - Photo Booth sub types
 */
typedef enum E_MarshallApi_InfoPhotoBoothSubType_tag
{
    MARSHALLAPI_INFO_PHOTO_BOOTH_SUB_TYPE_RESERVED             = 0,   
    MARSHALLAPI_INFO_PHOTO_BOOTH_SUB_TYPE_1                    = 1,   
    MARSHALLAPI_INFO_PHOTO_BOOTH_SUB_TYPE_2                    = 2,
    
    MARSHALLAPI_INFO_PHOTO_BOOTH_SUB_TYPE_MAX,

} E_MarshallApi_InfoPhotoBoothSubType;

/**
 * @name 	E_MarshallApi_InfoEvChargerSubType
 * @brief	Firmware info - EV (electric vehicle) Charger sub types
 */
typedef enum E_MarshallApi_InfoEvChargerSubType_tag
{
    MARSHALLAPI_INFO_EV_CHARGER_SUB_TYPE_RESERVED             = 0,   
    MARSHALLAPI_INFO_EV_CHARGER_SUB_TYPE_1                    = 1,   
    MARSHALLAPI_INFO_EV_CHARGER_SUB_TYPE_2                    = 2,
    
    MARSHALLAPI_INFO_EV_CHARGER_SUB_TYPE_MAX,

} E_MarshallApi_InfoEvChargerSubType;


/**
 * @name 	E_MarshallApi_InfoBeverageMachineSubType
 * @brief	Firmware info - Beverage Machine sub types
 */
typedef enum E_MarshallApi_InfoBeverageMachineSubType_tag
{
    MARSHALLAPI_INFO_BEVERAGE_MACHINE_SUB_TYPE_RESERVED             = 0,   
    MARSHALLAPI_INFO_BEVERAGE_MACHINE_SUB_TYPE_1                    = 1,   
    MARSHALLAPI_INFO_BEVERAGE_MACHINE_SUB_TYPE_2                    = 2,
    
    MARSHALLAPI_INFO_BEVERAGE_MACHINE_SUB_TYPE_MAX,

} E_MarshallApi_InfoBeverageMachineSubType;

/**
* @name 	E_MarshallApi_InfoWaterFillingSubType
* @brief	Firmware info - Water filling sub types
*/
typedef enum E_MarshallApi_InfoWaterFillingSubType_tag
{
    MARSHALLAPI_INFO_WATER_FILLING_SUB_TYPE_RESERVED             = 0,   
    MARSHALLAPI_INFO_WATER_FILLING_SUB_TYPE_1                    = 1,   
    MARSHALLAPI_INFO_WATER_FILLING_SUB_TYPE_2                    = 2,

    MARSHALLAPI_INFO_WATER_FILLING_SUB_TYPE_MAX,

} E_MarshallApi_InfoWaterFillingSubType;

/**
* @name 	E_MarshallApi_InfoLockerSubType
* @brief	Firmware info - Locker sub types
*/
typedef enum E_MarshallApi_InfoLockerSubType_tag
{
    MARSHALLAPI_INFO_LOCKER_SUB_TYPE_RESERVED             = 0,   
    MARSHALLAPI_INFO_LOCKER_SUB_TYPE_1                    = 1,   
    MARSHALLAPI_INFO_LOCKER_SUB_TYPE_2                    = 2,

    MARSHALLAPI_INFO_LOCKER_SUB_TYPE_MAX,

} E_MarshallApi_InfoLockerSubType;

/**
* @name 	E_MarshallApi_InfoRetailSubType
* @brief	Firmware info - Retail sub types
*/
typedef enum E_MarshallApi_InfoRetailSubType_tag
{
    MARSHALLAPI_INFO_RETAIL_SUB_TYPE_RESERVED             = 0,   
    MARSHALLAPI_INFO_RETAIL_SUB_TYPE_1                    = 1,   
    MARSHALLAPI_INFO_RETAIL_SUB_TYPE_2                    = 2,

    MARSHALLAPI_INFO_RETAIL_SUB_TYPE_MAX,

} E_MarshallApi_InfoRetailSubType;


/**
* @name 	E_MarshallApi_InfoLaundryMachineSubType
* @brief	Firmware info - Laundry sub types
*/
typedef enum E_MarshallApi_InfoLaundryMachineSubType_tag
{
    MARSHALLAPI_INFO_LAUNDRY_MACHINE_SUB_TYPE_RESERVED              = 0,   
    MARSHALLAPI_INFO_LAUNDRY_MACHINE_SUB_TYPE_1                     = 1,   
    MARSHALLAPI_INFO_LAUNDRY_MACHINE_SUB_TYPE_2                     = 2,

    MARSHALLAPI_INFO_LAUNDRY_MACHINE_SUB_TYPE_MAX,

} E_MarshallApi_InfoLaundryMachineSubType;

/**
* @name 	E_MarshallApi_InfoEMoneySubType
* @brief	Firmware info - E Money sub types
*/
typedef enum E_MarshallApi_InfoEMoneySubType_tag
{
    MARSHALLAPI_INFO_E_MONEY_SUB_TYPE_RESERVED                      = 0,   
    MARSHALLAPI_INFO_E_MONEY_SUB_TYPE_1                             = 1,   
    MARSHALLAPI_INFO_E_MONEY_SUB_TYPE_2                             = 2,

    MARSHALLAPI_INFO_E_MONEY_SUB_TYPE_MAX,

} E_MarshallApi_InfoEMoneySubType;


/**
 * @brief	Device Capabilities 
 */
#define	MARSHALLAPI_DEV_CAPB_MAGSTRIPE_BIT_OFFSET                           0
#define	MARSHALLAPI_DEV_CAPB_MAGSTRIPE_BIT_MASK			                    0x0001
#define	MARSHALLAPI_DEV_CAPB_CONTACT_BIT_OFFSET                             1
#define	MARSHALLAPI_DEV_CAPB_CONTACT_BIT_MASK			                    0x0002
#define	MARSHALLAPI_DEV_CAPB_CONTACTLESS_BIT_OFFSET                         2
#define	MARSHALLAPI_DEV_CAPB_CONTACTLESS_BIT_MASK		                    0x0004  
#define	MARSHALLAPI_DEV_CAPB_KEYPAD_BIT_OFFSET                              3
#define	MARSHALLAPI_DEV_CAPB_KEYPAD_BIT_MASK		                        0x0008 
#define	MARSHALLAPI_DEV_CAPB_DISPLAY_BIT_OFFSET                             4
#define	MARSHALLAPI_DEV_CAPB_DISPLAY_BIT_MASK		                        0x0010 
#define	MARSHALLAPI_DEV_CAPB_TOUCH_SCREEN_BIT_OFFSET                        5
#define	MARSHALLAPI_DEV_CAPB_TOUCH_SCREEN_BIT_MASK		                    0x0020 
#define	MARSHALLAPI_DEV_CAPB_MULTI_SESSION_BIT_OFFSET                       6
#define	MARSHALLAPI_DEV_CAPB_MULTI_SESSION_BIT_MASK		                    0x0040 
#define	MARSHALLAPI_DEV_CAPB_PROP_MIFARE_CARD_APPROVED_BY_VMC_BIT_OFFSET    7
#define	MARSHALLAPI_DEV_CAPB_PROP_MIFARE_CARD_APPROVED_BY_VMC_BIT_MASK		0x0080 
#define	MARSHALLAPI_DEV_CAPB_VEND_REQ_PRICE_IS_NOT_FINAL_BIT_OFFSET         8
#define	MARSHALLAPI_DEV_CAPB_VEND_REQ_PRICE_IS_NOT_FINAL_BIT_MASK           0x0100 
#define	MARSHALLAPI_DEV_CAPB_PROP_MAG_CARD_APPROVED_BY_VMC_BIT_OFFSET       9
#define	MARSHALLAPI_DEV_CAPB_PROP_MAG_CARD_APPROVED_BY_VMC_BIT_MASK		    0x0200
#define	MARSHALLAPI_DEV_CAPB_FTL_DATA_BIT_OFFSET                            10
#define	MARSHALLAPI_DEV_CAPB_FTL_DATA_BIT_MASK		                        0x0400


					/************************************************/
					/*		    		C O N F I G	  	 			*/
					/************************************************/
/**
 * @name 	S_MarshallApi_ConfigParams
 * @brief	The Config Params structure
 */
typedef P_STRUCT S_MarshallApi_ConfigParams_tag
{

	uint8_t			ProtocolVerMajor;					        /** Protocol version (Major) 			*/
	uint8_t			ProtocolVerMinor;					        /** Protocol version (Minor) 			*/
	uint8_t			PeripheralID;						        /** Peripheral ID			 			*/
	uint32_t		KeepAlivePollInterval;				        /** Keep Alive/Poll Interval in mSec 	*/
	uint8_t			Language;							        /** Language		 					*/
	uint8_t			CountryCode[3];						        /** Country Code 	 					*/
	uint8_t			CurrencyCode[3];					        /** Currency Code 	 					*/
	uint8_t			DecimalPlace;						        /** Decimal Place 	 					*/
	uint8_t			AmitSerialNumber[16];				        /** Amit SerialNumber					*/
	uint16_t		MaxMsgLength;						        /** Max Message Length 					*/
	uint8_t			MerchantID[16];     				        /** Merchant ID     					    */
	uint8_t			AcqTerminalID[20];	    			        /** Acquirer Terminal ID				    */
	uint8_t			MachineLocation[100];				        /** Machine Location (Dynamic descriptor)	*/

}S_MarshallApi_ConfigParams;

					/************************************************/
					/*		   T R A N S F E R      D A T A 		*/
					/************************************************/
/**
 * @name 	E_MarshallApi_TransferDataTags
 * @brief	Transfer data tags
 */
typedef enum E_MarshallApi_TransferDataTags_tag
{
    MARSHALLAPI_TRANSFER_DATA_TAG_TXN_ID                        = 1,    /** Transaction ID                      */
    MARSHALLAPI_TRANSFER_DATA_TAG_CHOOSE_PRODUCT_TIMEOUT        = 2,    /** The peripheral can update the Amit timeout “Choose Product Timeout”.
                                                                            If it set to zero the Amit will not play and display the choose product message.
                                                                            It is possible to update this parameter only when the Amit is in idle state and not during a session.   */
    MARSHALLAPI_TRANSFER_DATA_CARD_TYPE                         = 3,    /** Card type       (Data - E_MarshallApi_TDCardType,           Data size - 1 byte) */
    MARSHALLAPI_TRANSFER_DATA_CARD_ENTRY_MODE                   = 4,    /** Card entry mode (Data - E_MarshallApi_TDCardEntryType,      Data size - 1 byte) */
    MARSHALLAPI_TRANSFER_DATA_CARD_BIN                          = 5,    /** Card BIN        (Data - ascii,                              Data size - 6 bytes) */
    MARSHALLAPI_TRANSFER_DATA_CARD_BIN_HASH                     = 6,    /** Card BIN Hash   (Data - int,                                Data size - 20 bytes) */ 
    MARSHALLAPI_TRANSFER_DATA_CARD_UID                          = 7,    /** Card UID        (Data - int,                                Data size - 4,7 or 10 bytes) */ 
    MARSHALLAPI_TRANSFER_DATA_VMC_AUTH_STATUS                   = 8,    /** When the VMC finishing authorize a propriety card it will send auth status to the Amit  */
    MARSHALLAPI_TRANSFER_DATA_COM_STATUS                        = 9,    /** The Amit - server communication status (0 - OK, else - error, Data size  - 1) */
    MARSHALLAPI_TRANSFER_DATA_FTL                               = 10,   /** FTL - data */              
    MARSHALLAPI_TRANSFER_DATA_TAG_CREATE_LAYOUT                 = 11,   /** Layout - 4 bytes */
    MARSHALLAPI_TRANSFER_DATA_TAG_UPDATE_LAYOUT                 = 12,   /** Update layout by ExtraData field (4 Bytes) + N bytes */
    MARSHALLAPI_TRANSFER_DATA_CARD_FOUR_LAST_DIGITS             = 13,   /** Card four last digits (Data - int,                                Data size - 20 bytes) */ 
    
//__MARSHALL_EGGED__
    MARSHALLAPI_TRANSFER_DATA_PRODUCT_CODE                      = 14,   /** Product code */
    MARSHALLAPI_TRANSFER_DATA_PRODUCT_PRICE                     = 15,   /** Product price */

    MARSHALLAPI_TRANSFER_DATA_GENERAL_PURPOSE                   = 16,   /** A general purpose tag */

    MARSHALLAPI_TRANSFER_DATA_TAG_MAX,

} E_MarshallApi_TransferDataTags;

#define MARSHALL_TXN_ID_SIZE                                    8

/**
 * @name 	S_MarshallApi_Tlv
 * @brief	The transfer data TLV structure
 */
typedef P_STRUCT S_MarshallApi_Tlv_tag
{    
	uint8_t			Tag;
    uint8_t			Length;
    uint8_t         DataFirstByte;

}S_MarshallApi_Tlv;

#define MARSHALLAPI_EXTENDED_TAG_FLAG                           0x80

/**
 * @name 	S_MarshallApi_TlvExtended
 * @brief	The extended transfer data TLV structure
 */
typedef P_STRUCT S_MarshallApi_TlvExtended_tag
{    
	uint8_t		    Tag[2];
    uint16_t		Length;
    uint8_t         DataFirstByte;

}S_MarshallApi_TlvExtended;


/**
 * @name 	E_MarshallApi_TDCardType
 * @brief	Transfer data card type
 */
typedef enum E_MarshallApi_TDCardType_tag
{
    MARSHALLAPI_TRANSFER_DATA_UNKOWN_CARD_TYPE = 0,                 /* Unknown	            */
    MARSHALLAPI_TRANSFER_DATA_PROPRIETARY_CARD_TYPE,                /* Proprietary	        */
    MARSHALLAPI_TRANSFER_DATA_VISA_CARD_TYPE,                       /* Visa	                */
    MARSHALLAPI_TRANSFER_DATA_MASTER_CARD_CARD_TYPE,                /* Master Card          */
    MARSHALLAPI_TRANSFER_DATA_CHINA_UNION_PAY_CARD_TYPE,            /* China Union Pay	    */
    MARSHALLAPI_TRANSFER_DATA_MAESTRO_CARD_TYPE,                    /* Maestro  	        */
    MARSHALLAPI_TRANSFER_DATA_INTERAC_CARD_TYPE,                    /* Interac  	        */
    MARSHALLAPI_TRANSFER_DATA_MONYX_CARD_TYPE,                      /* Monyx  	            */
                                                                    
    MARSHALLAPI_TRANSFER_DATA_CARD_TYPE_MAX,                       

}E_MarshallApi_TDCardType;

/**
 * @name 	E_MarshallApi_TDCardEntryType
 * @brief	Transfer data card entry type
 */
typedef enum E_MarshallApi_TDCardEntryType_tag
{ 
    MARSHALLAPI_TRANSFER_DATA_MSR_SWIPE_CARD_ENTRY_TYPE = 1,         /* Mag stripes	        */
    MARSHALLAPI_TRANSFER_DATA_CONTACTLESS_CARD_ENTRY_TYPE,           /* Contactless	        */
    MARSHALLAPI_TRANSFER_DATA_CONTACT_CARD_ENTRY_TYPE,               /* Contact	            */
    MARSHALLAPI_TRANSFER_DATA_MIFARE_CARD_ENTRY_TYPE,                /* MiFare	            */
    MARSHALLAPI_TRANSFER_DATA_HID_CARD_ENTRY_TYPE,                   /* HID	                */
    MARSHALLAPI_TRANSFER_DATA_NFC_CARD_ENTRY_TYPE,                   /* NFC	                */
    MARSHALLAPI_TRANSFER_DATA_CNOUS_CARD_ENTRY_TYPE,                 /* CNOUS	            */
    MARSHALLAPI_TRANSFER_DATA_KEYPAD_ENTRY_TYPE,                     /* Keypad	            */
    MARSHALLAPI_TRANSFER_DATA_MOBILE_ENTRY_TYPE,                     /* Mobile	            */
    MARSHALLAPI_TRANSFER_DATA_QR_ENTRY_TYPE,                         /* QR	                */
    MARSHALLAPI_TRANSFER_DATA_BLE_ENTRY_TYPE,                        /* BLE	                */  
        
    MARSHALLAPI_TRANSFER_DATA_CARD_ENTRY_TYPE_MAX,

}E_MarshallApi_TDCardEntryType;


					/************************************************/
					/*		    		S T A T U S	  	 			*/
					/************************************************/

/**
* @name 	S_MarshallApi_Status
* @brief	Status message
*/
typedef P_STRUCT S_MarshallApi_Status_tag
{
	uint8_t			Type;				                        /** According to E_MarshallApi_StatusType   */
    uint16_t		DataSize;		                            /** Additional status data size             */
    uint8_t         DataFirstByte;                              /** Status additional data                  */
    
}S_MarshallApi_Status;

/**
* @name 	E_MarshallApi_StatusType
* @brief	Firmware info - type
*/
typedef enum E_MarshallApi_StatusType_tag
{
    MARSHALLAPI_STATUS_TYPE_UNEXPECTED_ERR              = 0,       		/** Unexpected error                                */
	MARSHALLAPI_STATUS_TYPE_TIMEOUT                     = 1,            /** Process time-out                                */
	MARSHALLAPI_STATUS_TYPE_OUT_OF_SEQUENCE             = 2,      		/** Received out of sequence command                */
	MARSHALLAPI_STATUS_TYPE_PEND_SERV_DATA              = 3,			/** Pending 3rd party communication data received   */
    MARSHALLAPI_STATUS_TYPE_CLOSE_SESSION_STATUS        = 4,			/** In multi session, a response for close session  */
    MARSHALLAPI_STATUS_TYPE_MACHINE_STATUS              = 5,			/** Machine status                                  */
    MARSHALLAPI_STATUS_TYPE_FTP_STATUS                  = 6,			/** FTP status                                      */
    MARSHALLAPI_STATUS_TYPE_MACHINE_INHIBIT             = 7,			/** Machine inhibit                                 */
    
    /** This session status messages will be used only when the Marshall channel isn't handling  the vending                */
    MARSHALLAPI_STATUS_TYPE_SESSION_PRODUCT_SELECTED    = 100,			/** Product selected                                */
    MARSHALLAPI_STATUS_TYPE_SESSION_VEND_APPROVE        = 101,			/** Vending approve                                 */
    MARSHALLAPI_STATUS_TYPE_SESSION_VEND_DECLINE        = 102,			/** Vending decilne                                 */
    MARSHALLAPI_STATUS_TYPE_SESSION_VEND_SUCCESS        = 103,			/** Vending success                                 */
    MARSHALLAPI_STATUS_TYPE_SESSION_VEND_FAILURE        = 104,			/** Vending failure                                 */
    MARSHALLAPI_STATUS_TYPE_SESSION_VEND_CANCEL         = 105,			/** Vending cancel                                  */
    

	MARSHALLAPI_STATUS_TYPE_MAX,

} E_MarshallApi_StatusType;
    
/**
* @name 	E_MarshallApi_CloseSessionRetVal
* @brief	Close session return value
*/
typedef enum E_MarshallApi_CloseSessionRetVal_tag
{
    MARSHALLAPI_CLOSE_SESSION_OK_RET_VAL                = 0,       	/** Status OK                                       */
    MARSHALLAPI_CLOSE_SESSION_ITEM_NOT_FOUND_RET_VAL    = 1,	    /** Item not found                                  */
    MARSHALLAPI_CLOSE_SESSION_UNEXPECTED_ERR_RET_VAL    = 2,	    /** Unexpected error                                */

	MARSHALLAPI_CLOSE_SESSION_RET_VAL_MAX,

} E_MarshallApi_CloseSessionRetVal;    

/**
* @name 	E_MarshallApi_MachineStatus
* @brief	Machine status describtion
*/
typedef enum E_MarshallApi_MachineStatus_tag
{
    MARSHALLAPI_MACHINE_STATUS_CONNECTED                = 0,       	/** Machine connected                               */
    MARSHALLAPI_MACHINE_STATUS_NOT_CONNECTED            = 1,	    /** Machine not connected                           */
    MARSHALLAPI_MACHINE_STATUS_NOT_READY                = 2,	    /** Machine not ready                               */

	MARSHALLAPI_MACHINE_STATUS_MAX,

} E_MarshallApi_MachineStatus; 

					/************************************************/
					/*		  D I S P L A Y   M E S S A G E	  	    */
					/************************************************/
/**
 * @name 	S_MarshallApi_DisplaysMessage
 * @brief	A message to display on LCD
 */
typedef P_STRUCT S_MarshallApi_DisplaysMessage_tag
{
	uint8_t			FirstByteOfMsgToDisplay;

}S_MarshallApi_DisplaysMessage;

					/************************************************************/
					/*		  D I S P L A Y   M E S S A G E	  S T A T U S	    */
					/************************************************************/
/**
 * @name 	S_MarshallApi_DisplaysMsgStatus
 * @brief	A response to display message
 */
typedef P_STRUCT S_MarshallApi_DisplaysMsgStatus_tag
{
	uint8_t			DisplayStatus;

}S_MarshallApi_DisplaysMsgStatus;

/**
* @name 	E_MarshallApi_DisplaysMsgStatus
* @brief	The display message status 
*/
typedef enum E_MarshallApi_DisplaysMsgStatus_tag
{
	MARSHALLAPI_DISPLAYS_MSG_STATUS_OK      = 0,      	        /** Display message OK         */
	MARSHALLAPI_DISPLAYS_MSG_STATUS_ERR     = 1,		        /** Display message error      */

	MARSHALLAPI_DISPLAYS_MSG_STATUS_MAX,

} E_MarshallApi_DisplaysMsgStatus;

					/************************************************/
					/*		   M O D E M     S T A T U S	        */
					/************************************************/

/**
* @name 	E_MarshallApi_ModemRetVal
* @brief	The modem return value
*/
typedef enum E_MarshallApi_ModemRetVal_tag
{
	MARSHALLAPI_MODEM_RET_VAL_OK                            = 0,           
    MARSHALLAPI_MODEM_RET_VAL_FAIL,
    MARSHALLAPI_MODEM_RET_VAL_BUSY, 
    MARSHALLAPI_MODEM_RET_VAL_PARAM_IN,
    MARSHALLAPI_MODEM_RET_VAL_CMD,
    MARSHALLAPI_MODEM_RET_VAL_SOCKET_CLOSED,
    
	MARSHALLAPI_MODEM_RET_VAL_NO_AVAILABLE_RESOURCE         = 0x80, 
    MARSHALLAPI_MODEM_RET_VAL_NOT_SUPPORTED_SOCKET_TYPE,   
    
	MARSHALLAPI_MODEM_RET_VAL_MAX,

}E_MarshallApi_ModemRetVal;


/**
 * @name 	S_MarshallApi_ModemStatus
 * @brief	The modem status   
 */
typedef P_STRUCT S_MarshallApi_ModemStatus_tag
{
	uint8_t			Cmd;                                        /** The command the modem responding to (0 incase the status message isn't a response) */	
    uint8_t         ModemRetVal;                                /** E_MarshallApi_ModemRetVal                       */
    uint8_t         ModemExtraData;                             /** If the error isn't busy it will contain the modem err number
                                                                       In case of busy - it will contain an estimate busy time in seconds*/

}S_MarshallApi_ModemStatus;


					/************************************************/
					/*		       O P E N    S O C K E T	  		*/
					/************************************************/
/**
 * @name 	S_MarshallApi_OpenSocket
 * @brief	Open a socket for communication with a server.  
 */
typedef P_STRUCT S_MarshallApi_OpenSocket_tag
{
	uint8_t			ServerDestination;				            /** Server destination 			                            */
	uint8_t			Protocol;					                /** Protocol type 			                                */
	uint16_t		Port;						                /** Port number			 			                        */
	uint8_t		    ServerAddrFirstByte;	                    /** IP or DNS address (ASCII string with variable length    */
    /* In Marshall version >= 2.0  after the server address will come the data max lentgh + Socket timeout
    uint16_t        DataMaxLength;	                            Packet limit size   
    uint16_t        SocketTimeout;	                            Socket timeout   */

}S_MarshallApi_OpenSocket;



/**
* @name 	E_MarshallApi_OpenSocketDest
* @brief	Open socket  - Destination 
*/
typedef enum E_MarshallApi_OpenSocketDest_tag
{
	MARSHALLAPI_OPEN_SOCKET_DEST_NAYAX_SERVER           = 0,    /** Nayax’s Server          */
	MARSHALLAPI_OPEN_SOCKET_DEST_TRD_PARTIY_SERVER      = 1,    /** 3rd party's Server      */

	MARSHALLAPI_OPEN_SOCKET_DEST_MAX,

} E_MarshallApi_OpenSocketDest;

/**
* @name 	E_MarshallApi_OpenSocketProtocol
* @brief	Open socket  - Protocol type
*/
typedef enum E_MarshallApi_OpenSocketProtocol_tag
{
	MARSHALLAPI_OPEN_SOCKET_PROTOCOL_TCP        = 0,            /** TCP     */
	MARSHALLAPI_OPEN_SOCKET_PROTOCOL_UDP        = 1,            /** UDP     */
    MARSHALLAPI_OPEN_SOCKET_PROTOCOL_FTP        = 2,            /** FTP     */

	MARSHALLAPI_OPEN_SOCKET_PROTOCOL_MAX,

} E_MarshallApi_OpenSocketProtocol;


					/************************************************/
					/*		       S E N D    D A T A  		        */
					/************************************************/
/**
 * @name 	S_MarshallApi_SendData
 * @brief	Send data to the opened socket.
 */
typedef P_STRUCT S_MarshallApi_SendData_tag
{
    uint8_t			    FirstByteOfData;		        /** The first byte of n data bytes      */
}S_MarshallApi_SendData;

					/************************************************/
					/*	     R E C E I V E D    D A T A    		    */
					/************************************************/

/**
 * @name 	S_MarshallApi_RcvData
 * @brief	The data receieved
 */
typedef P_STRUCT S_MarshallApi_RcvData_tag
{
    uint8_t			    FirstByteOfData;		        /** The first byte of n data bytes     */
}S_MarshallApi_RcvData;

					/************************************************/
					/*	     R X    C O N T R O L       		    */
					/************************************************/

/**
 * @name 	S_MarshallApi_RcvData
 * @brief	The data receieved
 */
typedef P_STRUCT S_MarshallApi_RxControl_tag
{
    uint8_t			    ResumePause;		        /** 0 - Resume, 1- Pause  */
}S_MarshallApi_RxControl;


					/************************************************/
					/*		           T R A C E  	 	            */
					/************************************************/
/**
 * @name 	S_MarshallApi_Trace
 * @brief	Trace command
 */
typedef P_STRUCT S_MarshallApi_Trace_tag
{

	uint16_t		TraceNumber;					    /** Peripheral trace number 			    */
	uint8_t			ParametersNum;					    /** Number of Parameters, values: 0, 1 or 2 */
	uint16_t		Parameter1 ;						/** Parameter 1			 			        */
	uint16_t		Parameter2 ;						/** Parameter 2			 			        */

}S_MarshallApi_Trace;

					/************************************************/
					/*		           A L E R T 	                */
					/************************************************/

#define MARSHALL_API_ALERT_NUMBER_SIZE                  2

/**
 * @name 	S_MarshallApi_Alert
 * @brief	Alert command
 */
typedef P_STRUCT S_MarshallApi_Alert_tag
{

	uint16_t		AlertID;					        /** Peripheral alert ID 			        */
	uint8_t			AlertStringFirstByte;				/** Alert string                            */

}S_MarshallApi_Alert;

					/************************************************/
					/*		           T I M E   	                */
					/************************************************/

/**
 * @name 	S_MarshallApi_Time
 * @brief	Time command
 */
typedef P_STRUCT S_MarshallApi_Time_tag
{
	uint8_t		    Year;					        /** 0 - 99	*/
	uint8_t			Month;				            /** 1 - 12  */
    uint8_t         Day;                            /** 1 - 31  */
    uint8_t         Hour;                           /** 0 - 23  */
    uint8_t         Min;                            /** 0 - 59  */
    uint8_t         Sec;                            /** 0 - 59  */

}S_MarshallApi_Time;

					/************************************************/
					/*		    S E T     P A R A M E T E R   	    */
					/************************************************/

/**
 * @name 	S_MarshallApi_SetParam
 * @brief	Set peripheral parameter
 */
typedef P_STRUCT S_MarshallApi_SetParam_tag
{
	uint16_t		ParameterID;
	uint8_t			FirstByteOfParameterData;

}S_MarshallApi_SetParam;

typedef enum E_MarshallApi_SetParam_ParameterID
{
	MARSHALLAPI_SET_PARAM_PARAMETER_ID_WELCOME_MSG           = 0,    /** set the VPD1_eep.LCD1.welcome_msg */
        
	MARSHALLAPI_SET_PARAM_PARAMETER_ID_MAX,

} E_MarshallApi_SetParam_ParameterID;

					/************************************************/
					/*		  G E T  F I L E  V E R S I O N	  	    */
					/************************************************/
/**
 * @name 	S_MarshallApi_GetFileVersion
 * @brief	Get file version by File ID
 */
typedef P_STRUCT S_MarshallApi_GetFileVersion_tag
{
	uint16_t		FileID;

}S_MarshallApi_GetFileVersion;

					/******************************************/
					/*		  F I L E   V E R S I O N 	      */
					/******************************************/
/**
 * @name 	S_MarshallApi_FileVersion
 * @brief	File version
 */
typedef P_STRUCT S_MarshallApi_FileVersion_tag
{
	uint16_t		FileVersion;

}S_MarshallApi_FileVersion;

					/************************************************/
					/*		        S E N D   F I L E               */
					/************************************************/
/**
 * @name 	S_MarshallApi_SendFile
 * @brief	Send file/file header
 */
typedef P_STRUCT S_MarshallApi_SendFile_tag
{

	uint8_t		    Tag;   					            /** 0 - file header; 1 - file data */
	uint8_t		    LastPacketTag;			            /** 0 - not last; 1 - last         */
	uint8_t			FileOrHeaderFirstByte;				/** Data                           */

}S_MarshallApi_SendFile;

					/************************************************/
					/*		  C H E C K   F I L E    C R C          */
					/************************************************/
/**
 * @name 	S_MarshallApi_CheckFileCrc
 * @brief	Check File Crc
 */
typedef P_STRUCT S_MarshallApi_CheckFileCrc_tag
{

	uint8_t		    Tag;   					            /** 0 - check CRC; 1 - CRC  */
	uint16_t	    CRC16;			                    /** file CRC16              */
	uint8_t			FileNameFirstByte;				    /** File name               */

}S_MarshallApi_CheckFileCrc;

					/************************************************/
					/*		        F W    U P D A T E              */
					/************************************************/

#define POSAL_CONFIG_FILE_NAME_LENGTH          32

typedef P_STRUCT S_MarshallApi_ConfigFileStruct_tag
{
    uint8_t  BinFileName[POSAL_CONFIG_FILE_NAME_LENGTH];
    uint32_t PosAddr;
    uint8_t  ImgName[POSAL_CONFIG_FILE_NAME_LENGTH];
} S_MarshallApi_ConfigFileStruct;

/**
 * @name 	S_MarshallApi_FwUpdate
 * @brief	POSAL FW update
 */
typedef P_STRUCT S_MarshallApi_FwUpdate_tag
{

	uint8_t		                   PosCfgFileName[POSAL_CONFIG_FILE_NAME_LENGTH]; /** posal config file name */
	S_MarshallApi_ConfigFileStruct ConfigFileData;				                  /** Config file data       */
}S_MarshallApi_FwUpdate;

                    /************************************************/
                    /*		        PP SET EVENT   	                */
                    /************************************************/

#define MARSHALLAPI_PP_EVENT_TYPE_KEYBOARD            (1<<0)
#define MARSHALLAPI_PP_EVENT_TYPE_SWIPE               (1<<1)
#define MARSHALLAPI_PP_EVENT_TYPE_CONTACT             (1<<2)
#define MARSHALLAPI_PP_EVENT_TYPE_CONTACTLESS         (1<<3)
#define MARSHALLAPI_PP_EVENT_TYPE_CONTACTLESS_NFC     (1<<4)

/*
 * @name 	S_MarshallApi_PpSetEvent
 * @brief	PP Set Event command from Amit
 */
typedef P_STRUCT S_MarshallApi_PpSetEvent_tag
{
    uint8_t EventTypeActivation; /* bitmap (Bit 0 – Keyboard
                                            Bit 1 – Swipe
                                            Bit 2 – Contact
                                            Bit 3 – Contactless
                                            Bit 4 – Contactless NFC) */
} S_MarshallApi_PpSetEvent;

                    /************************************************/
					/*		           PP EVENT   	                */
					/************************************************/
#define CARD_DATA_VALUE_LEN 128

typedef enum E_MarshallApi_PaymentType_tag
{
    MARSHALLAPI_PP_CC_MAGSTRIPE_PAYMENT_TYPE                = 1,
    MARSHALLAPI_PP_CC_CONTACT_PAYMENT_TYPE                  = 2,
    MARSHALLAPI_PP_CC_CONTACTLESS_PAYMENT_TYPE              = 3,
    MARSHALLAPI_PP_CC_CONTACTLESS_MAGSTRIPE_PAYMENT_TYPE    = 4,
    MARSHALLAPI_PP_CC_MIFARE_PAYMENT_TYPE                   = 5,
    MARSHALLAPI_PP_CC_HID_PAYMENT_TYPE                      = 6,
    MARSHALLAPI_PP_CC_QR_PAYMENT_TYPE                       = 7,
    MARSHALLAPI_PP_CC_PREPAID_MAGSTRIPE_PAYMENT_TYPE        = 11,
    MARSHALLAPI_PP_CC_PREPAID_CONTACT_PAYMENT_TYPE          = 12,
    MARSHALLAPI_PP_CC_PREPAID_CONTACTLESS_PAYMENT_TYPE      = 13,

    MARSHALLAPI_PP_CC_MAX_PAYMENT_TYPE,
}E_MarshallApi_PaymentType;

typedef enum E_MarshallApi_PaymentCardType_tag
{
    MARSHALLAPI_PP_ASCII_CARD_DATA_TYPE = 1,
    MARSHALLAPI_PP_BINARY_CARD_DATA_TYPE = 2,
    MARSHALLAPI_PP_BCD_CARD_DATA_TYPE = 3,

    MARSHALLAPI_PP_MAX_CARD_DATA_TYPE,
}E_MarshallApi_PaymentCardType;

typedef P_STRUCT S_MarshallApi_PpCardData_tag
{
    uint8_t  Bin[6];
    uint8_t  PAN[4];
    uint8_t  AcquirerID[12];
    uint8_t  TransactionID[8];
    uint8_t  TimeStampID[14];
    uint8_t  SHA256[32];
} S_MarshallApi_PpCardData;

/*
 * @name 	S_MarshallApi_PpEvent
 * @brief	PP Event command
 */
typedef P_STRUCT S_MarshallApi_PpEvent_tag
{
	uint8_t EventType;				            /* bitmap ( Bit 0 – Keyboard
                                                            Bit 1 – Swipe
                                                            Bit 2 – Contact 
                                                            Bit 3 – Contactless 
                                                            Bit 4 – Contactless NFC) */
	uint8_t	PaymentTypeOrKeyValue;                 /* 1 - 6 & 11 - 13 - Card Type OR 
                                                   0 - 9 keys 0 - 9 & 
                                                   0x0A – CLEAR
                                                   0x0B – CANCEL
                                                   0x0D – ENTER
                                                   0x10 – F
                                                   0x11 – F1
                                                   0x12 – F2
                                                   0x13 – F3
                                                   0x14 – F4 */
    uint8_t CardDataType;                       /* 1 – ASCII 
                                                   2 – Binary 
                                                   3 – BCD  */
    S_MarshallApi_PpCardData  CardDataValue; /* Credit Card:
                                                    - BIN						                  (6 bytes)
                                                    - PAN 4 last digits				              (4 bytes)
                                                    - Acquirer ID					              (12 bytes)
                                                    - Transaction ID (unique, controlled by Bank) (8 bytes)
                                                    - Time Stamp YYYYMMDDHHMMSS		              (14 bytes)
                                                    - SHA256 signature of PAN			          (32 bytes)
                                                   OR Prepaid:
                                                    UID + Optional Proprietary data		          (up to 128 bytes) */
} S_MarshallApi_PpEvent;

					/************************************************/
					/*		     PP Transaction Cancel              */
					/************************************************/
#define MARSHALLAPI_PP_TRANSACTION_VOID_CANCEL_TYPE                             0
#define MARSHALLAPI_PP_TRANSACTION_DECLINE_CANCEL_TYPE                          1
#define MARSHALLAPI_PP_TRANSACTION_SERVER_TIMEOUT_CANCEL_TYPE                   2
#define MARSHALLAPI_PP_TRANSACTION_WRONG_PIN_CODE_CANCEL_TYPE                   3
#define MARSHALLAPI_PP_TRANSACTION_CANCELED_BY_CONSUMER_CANCEL_TYPE             10           
#define MARSHALLAPI_PP_TRANSACTION_CONSUMER_TIMEOUT_CANCEL_TYPE                 11           
#define MARSHALLAPI_PP_TRANSACTION_VENDING_MACHINE_COM_ERR_CANCEL_TYPE          12
/*
 * @name 	S_MarshallApi_PpTrnCancel
 * @brief	PP Transaction Cancel command
 */
typedef P_STRUCT S_MarshallApi_PpTrnCancel_tag
{
	uint8_t CancelCause; /* 0 – Refund/Void Transaction
                            1 – Transaction declined by bank
                            2 – Bank’s server communication Time Out
                            3 – Wrong PIN code (after X retries)
                            10 – Cancelled by consumer 
                            11 – Consumer Time Out 
                            12 – Vending Machine communication error 
                        */
} S_MarshallApi_PpTrnCancel;

					/************************************************/
					/*		     PP Transaction End                 */
					/************************************************/
#define MARSHALLAPI_PP_TRANSACTION_SUCCESSFULLY_END_TYPE                0
#define MARSHALLAPI_PP_TRANSACTION_DECLINED_END_TYPE                    1
#define MARSHALLAPI_PP_TRANSACTION_CANCELLED_END_TYPE                   2
#define MARSHALLAPI_PP_TRANSACTION_TIMEOUT_TYPE                         3

/*
 * @name 	S_MarshallApi_PpTrnEnd
 * @brief	PP End Transaction command
 */
typedef P_STRUCT S_MarshallApi_PpTrnEnd_tag
{
	uint8_t EndTrnState;    /* 0 – Transaction ended successfully (settled at bank) 
                               1 – Transaction declined (by bank) 
                               2 – Transaction Cancelled at bank after Auth.(product not dispensed, problem in VM, …)
                               3 – Transaction Time Out (no comm. with bank) */
} S_MarshallApi_PpTrnEnd;


					/************************************************/
					/*		        PP TRN REQUEST	                */
					/************************************************/
/*
 * @name 	S_MarshallApi_PpTrnRequest
 * @brief	PP Transaction Request command from Amit
 */
typedef P_STRUCT S_MarshallApi_PpTrnRequest_tag
{
	uint16_t ProductCode;
	uint32_t ProductPrice;
} S_MarshallApi_PpTrnRequest;

					/************************************************/
					/*		        PP DISPENSE CONFIRM             */
					/************************************************/
/*
 * @name 	S_MarshallApi_PpDispenseConfirm
 * @brief	PP Dispense Confirm command from Amit
 */
typedef P_STRUCT S_MarshallApi_PpDispenseConfirm_tag
{
	uint8_t DispenseResult; /*  0 – OK
                                1 – Time Out
                                2 – Canceled by user 
                                3 – Canceled by Vending Machine 
                                4 – No credit (unlikely to happen) 
                                5 – Vending Machine Not Idle 
                                6 – Product can NOT be dispensed 
                                7 – Vending Machine Powered Down 
                                8 – Power Down during dispense 
                                9 – Vending Machine canceled during auth. Process */
} S_MarshallApi_PpDispenseConfirm;

                    /************************************************/
                    /*		     M D B    C O M A N D S   (VMC)     */
                    /************************************************/

#define MARSHALLAPI_MDB_CMD_OFFSET				        0
#define MARSHALLAPI_MDB_SUB_CMD_OFFSET			        1

/**
 * @name 	E_MarshallApi_MdbCommandsCode
 * @brief	The supported MDB commands code (peripheral -> amit)
 */
typedef enum    E_MarshallApi_MdbCommandsCode_tag
{
    MARSHALLAPI_MDB_CMD_CODE_VEND                       = 0x13,        
    MARSHALLAPI_MDB_CMD_CODE_READER                     = 0x14,
    MARSHALLAPI_MDB_CMD_CODE_EXPANSION                  = 0x17,
   
    MARSHALLAPI_MDB_CMD_CODE_MAX,

} E_MarshallApi_MdbCommandsCode;

/**
 * @name 	E_MarshallApi_MdbVendSubCommandsCode
 * @brief	The supported MDB vend sub commands code
 */
typedef enum    E_MarshallApi_MdbVendSubCommandsCode_tag
{
    MARSHALLAPI_MDB_CMD_CODE_VEND_REQEUST               = 0x0,        
    MARSHALLAPI_MDB_CMD_CODE_VEND_CANCEL                = 0x1,  
    MARSHALLAPI_MDB_CMD_CODE_VEND_SUCCESS               = 0x2,  
    MARSHALLAPI_MDB_CMD_CODE_VEND_FAILURE               = 0x3,  
    MARSHALLAPI_MDB_CMD_CODE_VEND_SESSION_COMPLETE      = 0x4, 
    MARSHALLAPI_MDB_CMD_CODE_CASH_SALE                  = 0x5,

    /** Extended MDB commands */
    MARSHALLAPI_MDB_CMD_CODE_VEND_CLOSE_SESSION         = 0x80,
    MARSHALLAPI_MDB_CMD_CODE_VEND_SESSION_TYPE          = 0x81,
#ifdef MARSHALL_MULTIVEND_PAY_PROJ
    MARSHALLAPI_MDB_CMD_CODE_EXTENDED_VEND_REQ          = 0x82,
    MARSHALLAPI_MDB_CMD_CODE_PREPAID_PAY                = 0x83,
    MARSHALLAPI_MDB_CMD_CODE_EXTENDED_VEND_SUCCESS      = 0x84,
#endif //MARSHALL_MULTIVEND_PAY_PROJ   
    MARSHALLAPI_MDB_CMD_CODE_VEND_MAX,

} E_MarshallApi_MdbVendSubCommandsCode;    

/**
 * @name 	E_MarshallApi_MdbReaderSubCommandsCode
 * @brief	The supported MDB reader sub commands code
 */
typedef enum    E_MarshallApi_MdbReaderSubCommandsCode_tag
{
    MARSHALLAPI_MDB_CMD_CODE_READER_DISABLE             = 0x0,        
    MARSHALLAPI_MDB_CMD_CODE_READER_ENABLE              = 0x1,  
    MARSHALLAPI_MDB_CMD_CODE_READER_CANCEL              = 0x2,  
   
    MARSHALLAPI_MDB_CMD_CODE_READER_MAX,

} E_MarshallApi_MdbReaderSubCommandsCode;

/**
 * @name 	E_MarshallApi_MdbFtlSubCommandsCode_tag
 * @brief	The supported MDB ftl commands
 */
typedef enum    E_MarshallApi_MdbFtlSubCommandsCode_tag
{
    MARSHALLAPI_MDB_FTL_CMD_SEND_BLOCK                  = 0xFC,
   
    MARSHALLAPI_MDB_FTL_CMD_MAX,

} E_MarshallApi_MdbFtlSubCommandsCode; 

/**
* @name 	S_MarshallApi_MdbCmdHeader
* @brief	MDB command header
*/
typedef P_STRUCT S_MarshallApi_MdbCmdHeader_tag
{
    uint8_t     Cmd;
    uint8_t     SubCmd;
}S_MarshallApi_MdbCmdHeader;

#ifdef MARSHALL_MULTIVEND_PAY_PROJ
/**
* @name 	S_MarshallApi_MdbExVendReqItem
* @brief	MDB Extended vend request command, for multi-item machines
*/
typedef P_STRUCT S_MarshallApi_MdbExVendReqItem_tag
{
    uint16_t	ItemNumber;         /* Product code */
	uint16_t	ItemPrice;          /* Product price */
    uint32_t    ItemQuantity;       /* Product Quantity */
    uint8_t     ItemUnit;           /* Measurement unit (KG/Liter/etc) */

}S_MarshallApi_MdbExVendReqItem;


#endif //MARSHALL_MULTIVEND_PAY_PROJ


/**
* @name 	S_MarshallApi_MdbVendRequest
* @brief	MDB vend request command
*/
typedef P_STRUCT S_MarshallApi_MdbVendRequest_tag
{
	uint16_t	ItemPrice;
	uint16_t	ItemNumber;

}S_MarshallApi_MdbVendRequest;

/**
* @name 	S_MarshallApi_MdbVendSuccess
* @brief	MDB vend success command
*/
typedef P_STRUCT S_MarshallApi_MdbVendSuccess_tag
{
	uint16_t	ItemNumber;

}S_MarshallApi_MdbVendSuccess;

/**
* @name 	S_MarshallApi_MdbVendCashSale
* @brief	MDB vend cash sale command
*/
typedef P_STRUCT S_MarshallApi_MdbVendCashSale_tag
{
	uint16_t	ItemPrice;
	uint16_t	ItemNumber;

}S_MarshallApi_MdbVendCashSale;

/**
* @name 	E_MarshallApi_SessionStatus
* @brief	MDB close session command - status definition
*/
typedef enum E_MarshallApi_SessionStatus_tag
{
	MARSHALLAPI_MDB_CLOSE_SESSION_CMD_STATUS_OK                     = 0x0, 
    MARSHALLAPI_MDB_CLOSE_SESSION_CMD_STATUS_USER_CANCEL            = 0x1, 
    MARSHALLAPI_MDB_CLOSE_SESSION_CMD_STATUS_FAIL_TO_DISPENCE       = 0x2,
    MARSHALLAPI_MDB_CLOSE_SESSION_CMD_STATUS_SESSION_TIMEOUT        = 0x3,
    
    MARSHALLAPI_MDB_CLOSE_SESSION_CMD_STATUS_MAX,

}E_MarshallApi_SessionStatus;

/**
* @name 	S_MarshallApi_MdbVendCloseSession
* @brief	(extended)MDB - close session command
*/
typedef P_STRUCT S_MarshallApi_MdbVendCloseSession_tag
{
	uint8_t	    SessionStatus;                      /** Acording to E_MarshallApi_SessionStatus */
	uint16_t	Price;
	uint16_t	ProductID;
    uint16_t    Quantity;

}S_MarshallApi_MdbVendCloseSession;

/**
* @name 	S_MarshallApi_MdbVendNewCloseSession
* @brief	(extended)MDB - close session command
*/
typedef P_STRUCT S_MarshallApi_MdbVendNewCloseSession_tag
{
    uint8_t	    SessionStatus;                      /** Acording to E_MarshallApi_SessionStatus */
    uint16_t	Price;
    uint16_t	ProductID;
    uint32_t    Quantity;
    uint8_t     UnitOfMeasure;

}S_MarshallApi_MdbVendNewCloseSession;

/**
* @name 	E_MarshallApi_MdbVendSessionType
* @brief	MDB session type command - type definition
*/
typedef enum E_MarshallApi_MdbVendSessionType
{
	MARSHALLAPI_MDB_SESSION_TYPE_VENDING        = 0x0, 
    MARSHALLAPI_MDB_SESSION_TYPE_INFO,
    
    MARSHALLAPI_MDB_SESSION_TYPE_MAX,

}E_MarshallApi_MdbVendSessionType;

/**
* @name 	S_MarshallApi_MdbVendSessionType
* @brief	(extended)MDB - session type command
*/
typedef P_STRUCT S_MarshallApi_MdbVendSessionType_tag
{
	uint8_t	    SessionType;                      /** Acording to E_MarshallApi_MdbVendSessionType */

}S_MarshallApi_MdbVendSessionType;

/**
 * @name 	U_MarshallApi_MdbFunctions
 * @brief	MDB functions
 */
typedef union U_MarshallApi_MdbFunctions_tag
{
    S_MarshallApi_MdbVendRequest	        MdbVendRequest;
    S_MarshallApi_MdbVendSuccess	        MdbVendSuccess;
    S_MarshallApi_MdbVendCloseSession       MdbVendCloseSession;
    S_MarshallApi_MdbVendNewCloseSession    MdbVendNewCloseSession;
    S_MarshallApi_MdbVendSessionType        MdbVendSessionType;
    S_MarshallApi_MdbVendCashSale           MdbVendCashSale;

}U_MarshallApi_MdbFunctions;

/**
* @name 	S_MarshallApi_MdbCmd
* @brief	MDB command
*/
typedef P_STRUCT S_MarshallApi_MdbCmd_tag
{
    S_MarshallApi_MdbCmdHeader  CmdHeader;
    
    U_MarshallApi_MdbFunctions  MdbFunctions;
}S_MarshallApi_MdbCmd;


                    /************************************************/
                    /*	 M D B   C O M A N D S  (Cashless Device)   */
                    /************************************************/

/**
 * @name 	E_MarshallApi_MdbCashlessDevCode
 * @brief	The supported MDB CashlessDev code (amit -> peripheral)
 */
typedef enum    E_MarshallApi_MdbCashlessDevCode_tag
{
	MARSHALLAPI_MDB_CMD_CASHLESS_DEV_CODE_BEGIN_SESSION			= 0x03,
	MARSHALLAPI_MDB_CMD_CASHLESS_DEV_CODE_SESSION_CANCEL_REQ	= 0x04,
	MARSHALLAPI_MDB_CMD_CASHLESS_DEV_CODE_SESSION_VEND_APPROVE	= 0x05,
	MARSHALLAPI_MDB_CMD_CASHLESS_DEV_CODE_SESSION_VEND_DENIED	= 0x06,
	MARSHALLAPI_MDB_CMD_CASHLESS_DEV_CODE_SESSION_END_SESSION	= 0x07,
	MARSHALLAPI_MDB_CMD_CASHLESS_DEV_CODE_CANCELED				= 0x08,
    
    MARSHALLAPI_MDB_CMD_CASHLESS_DEV_CODE_FTL_SEND_BLOCK		= 0x1D,
   
    MMARSHALLAPI_MDB_CMD_CASHLESS_DEV_CODE_MAX,

} E_MarshallApi_MdbCashlessDevCode;

/**
* @name 	S_MarshallApi_MdbCashlessDevCmdHeader
* @brief	MDB cashless device command header
*/
typedef P_STRUCT S_MarshallApi_MdbCashlessDevCmdHeader_tag
{
    uint8_t     Cmd;
}S_MarshallApi_MdbCashlessDevCmdHeader;

/**
* @name 	S_MarshallApi_MdbCashlessDevBeginSession
* @brief	MDB cashless device begin session 
*               Allow a patron to make a selection, but do not dispense product until funds are approved.
*/
typedef P_STRUCT S_MarshallApi_MdbCashlessDevBeginSession_tag
{
    uint16_t	TransCredit;                    /** Transaction credit */

}S_MarshallApi_MdbCashlessDevBeginSession;

/**
* @name 	S_MarshallApi_MdbCashlessDevVendApprove
* @brief	MDB cashless device vend approve
*               Allow the selected product to be dispensed.
*/
typedef P_STRUCT S_MarshallApi_MdbCashlessDevVendApprove_tag
{
	uint16_t	VendAmount;                     /** This is the amount deducted from the user, it may be surcharged or discounted. */
    
}S_MarshallApi_MdbCashlessDevVendApprove;

/**
 * @name 	U_MarshallApi_MdbCashlessDevFunctions
 * @brief	MDB cashless device functions
 */
typedef union U_MarshallApi_MdbCashlessDevFunctions_tag
{
    S_MarshallApi_MdbCashlessDevBeginSession    MdbCashlessDevBeginSession;
	S_MarshallApi_MdbCashlessDevVendApprove	    MdbCashlessDevVendApprove;
    
}U_MarshallApi_MdbCashlessDevFunctions;

/**
* @name 	S_MarshallApi_MdbCashlessDevCmd
* @brief	MDB command
*/
typedef P_STRUCT S_MarshallApi_MdbCashlessDevCmd_tag
{
    S_MarshallApi_MdbCashlessDevCmdHeader  MdbCashlessDevCmdHeader;
    
    U_MarshallApi_MdbCashlessDevFunctions  MdbCashlessDevCmdFunctions;
    
}S_MarshallApi_MdbCashlessDevCmd;


					/*************************************************/
					/*	     	 P A C K E T    U N I O N			 */
					/*************************************************/
/**
 * @name 	U_MarshallApi_Functions
 * @brief	All functions parameters
 */
typedef union U_MarshallApi_Functions_tag
{
	S_MarshallApi_FirmInfoParams	    FirmInfoParams;
	S_MarshallApi_ConfigParams		    ConfigParams;
    S_MarshallApi_Status                Status;
    S_MarshallApi_DisplaysMessage       DisplaysMessage;
    S_MarshallApi_DisplaysMsgStatus     DisplaysMsgStatus;
    S_MarshallApi_Tlv                   TransferData;
    S_MarshallApi_TlvExtended           TransferDataExtended;
    S_MarshallApi_MdbCmd                MdbCmd;
    S_MarshallApi_MdbCashlessDevCmd     MdbCashlessDevCmd;
    S_MarshallApi_ModemStatus           ModemStatus;
    S_MarshallApi_OpenSocket			OpenSocket;    
    S_MarshallApi_SendData              SendData;
    S_MarshallApi_RcvData               RcvData;
    S_MarshallApi_RxControl             RxControl;
    S_MarshallApi_Trace                 Trace;
    S_MarshallApi_Alert                 Alert;
    S_MarshallApi_Time                  Time;
    S_MarshallApi_SetParam              SetParam;
    S_MarshallApi_GetFileVersion        GetFileVersion;
    S_MarshallApi_FileVersion           FileVersion;
    S_MarshallApi_SendFile              SendFile;
    S_MarshallApi_PpSetEvent            PpSetEvent;
    S_MarshallApi_PpEvent               PpEvent;
    S_MarshallApi_PpTrnRequest          PpTrnRequest;
    S_MarshallApi_PpDispenseConfirm     PpDispenseConfirm;
    S_MarshallApi_PpTrnCancel           PpTrnCancel;
    S_MarshallApi_PpTrnEnd              PpTrnEnd;
    
}U_MarshallApi_Functions;

/**
 * @name 	S_MarshallApi_Packet
 * @brief	The Marshall packet structure
 */
typedef P_STRUCT S_MarshallApi_Packet_tag
{
	S_MarshallApi_PacketHeader	Header;

	U_MarshallApi_Functions		FunctionsParams;
}S_MarshallApi_Packet;

#if !defined STM32F2XX && !defined VPOS_PORJ
	/** Return to default pack definition */
	# pragma pack ()
#endif

#ifdef __cplusplus
}
#endif

#endif  //__MARSHALL_API_H__


