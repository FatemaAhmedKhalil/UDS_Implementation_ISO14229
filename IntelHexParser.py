###############################################################################################
###############################################################################################
################################### Author: Fatema Ahmed ######################################
##################################### Intel Hex Parser ########################################
####################################### Version: 1.00 #########################################
###############################################################################################
###############################################################################################

''' Parsing Data '''
NO_ERROR                                = 0
START_CODE_ERROR                        = 1
END_OF_FILE_ERROR                       = 2
EXTENDED_SEGMENT_ADDRESS_ERROR          = 3
START_SEGMENT_ADDRESS_ERROR             = 4
EXTENDED_LINEAR_ADDRESS_ERROR           = 5
START_LINEAR_ADDRESS_ERROR              = 6
CHECK_SUM_ERROR                         = 7
HEX_CONVERTER                           = 16
START_OF_RECORD                         = 1
BYTE_COUNT_SIZE                         = 2
ADDRESS_OFFSET_SIZE                     = 4
FLASH_START_SIZE                        = 4
DATA_SIZE                               = 2
RECORD_TYPE_SIZE                        = 2
CHECK_SUM_SIZE                          = 2
RECORD_TYPE_DATA                        = 0
RECORD_TYPE_END_OF_FILE                 = 1
RECORD_TYPE_EXTENDED_SEGMENT_ADDRESS    = 2
RECORD_TYPE_START_SEGMENT_ADDRESS       = 3
RECORD_TYPE_EXTENDED_LINEAR_ADDRESS     = 4
RECORD_TYPE_START_LINEAR_ADDRESS        = 5
DATA_RECORD_SIZE                        = 2
END_OF_FILE_RECORD_SIZE                 = 0
EXTENDED_SEGMENT_ADDRESS_RECORD_SIZE    = 4
START_SEGMENT_ADDRESS_RECORD_SIZE       = 8
EXTENDED_LINEAR_ADDRESS_RECORD_SIZE     = 4
START_LINEAR_ADDRESS_RECORD_SIZE        = 8

def hex_to_int(hex_str):
    return int(hex_str, 16)

def int_to_hex(n):
    return '{:08X}'.format(n)

def Parsing():
    ErrorState = NO_ERROR
    FlashStartAddress = 0
    
    ParsedData = []

    with open("GreenLED.hex", 'r') as file:
        lines = file.readlines()

    for Index in range(len(lines)):
        OneLine = lines[Index] 
    
        if OneLine[0] != ':':
            ErrorState = START_CODE_ERROR
            return ErrorState

        ''' 1 Byte  |  2 Bytes    |     4 Bytes     |    2 Bytes   |  According to Byte Count  |  2 Bytes   '''
        '''  Start  |  Byte Count |  Address Offset |  Record Type |           Data            | Check Sum  '''
        StartRecordIndex = START_OF_RECORD

        ByteCount = int(OneLine[StartRecordIndex:StartRecordIndex + BYTE_COUNT_SIZE], HEX_CONVERTER)
        StartRecordIndex += BYTE_COUNT_SIZE

        AddressOffset = int(OneLine[StartRecordIndex:StartRecordIndex + ADDRESS_OFFSET_SIZE], HEX_CONVERTER)
        StartRecordIndex += ADDRESS_OFFSET_SIZE

        RecordType = int(OneLine[StartRecordIndex:StartRecordIndex + RECORD_TYPE_SIZE], HEX_CONVERTER)
        StartRecordIndex += RECORD_TYPE_SIZE
        
        # Calculate checksum
        CheckSum = 0
        CheckSum += ByteCount
        CheckSum += (AddressOffset >> 8) & 0xFF
        CheckSum += (AddressOffset >> 0) & 0xFF
        CheckSum += RecordType

        # Switch for Record Type 
        if RecordType == RECORD_TYPE_DATA:
            # the only type we intrested only in data to be flashed
            oneLineParsedData = []
            Address = FlashStartAddress + AddressOffset
            Address = format(Address, '0' + str(FLASH_START_SIZE + ADDRESS_OFFSET_SIZE) + 'X')
            oneLineParsedData.append(Address)
            while ByteCount != 0: 
                Data = int(OneLine[StartRecordIndex:StartRecordIndex + DATA_SIZE], HEX_CONVERTER) # Extract one Line data and convert it to integer
                CheckSum += Data # Update checkSum                
                HexData = format(Data, '0' + str(DATA_SIZE) + 'X') # Convert data to hexadecimal string and pad it
                oneLineParsedData.append(HexData)

                StartRecordIndex += DATA_SIZE # Update Start Record Address
                ByteCount -= 1 # Decrement byte count
            ParsedData.append(oneLineParsedData)

        
        elif RecordType == RECORD_TYPE_END_OF_FILE:
            if OneLine.strip() != ":00000001FF":
                ErrorState = END_OF_FILE_ERROR;
                return ErrorState

        elif RecordType == RECORD_TYPE_EXTENDED_SEGMENT_ADDRESS:
                if ByteCount != 2: # the byte count for this mode is always 2
                    ErrorState = EXTENDED_SEGMENT_ADDRESS_ERROR
                    return ErrorState
                
                # get the upper 16 bit of the address
                SegmentAddress = int(OneLine[StartRecordIndex:StartRecordIndex + EXTENDED_SEGMENT_ADDRESS_RECORD_SIZE], HEX_CONVERTER)
                # Update checkSum  
                CheckSum += ((SegmentAddress >> 8) & 0xFF)
                CheckSum += ((SegmentAddress >> 0) & 0xFF)
                FlashStartAddress = SegmentAddress   << 4
                StartRecordIndex += EXTENDED_SEGMENT_ADDRESS_RECORD_SIZE # Update Start Record Address
        
        elif RecordType == RECORD_TYPE_START_SEGMENT_ADDRESS:
                if ByteCount != 4: # the byte count for this mode is always 4
                    ErrorState = START_SEGMENT_ADDRESS_ERROR
                    return ErrorState

                # get the upper 16 bit of the address
                SegmentAddress  = int(OneLine[StartRecordIndex:StartRecordIndex + START_SEGMENT_ADDRESS_RECORD_SIZE], HEX_CONVERTER)
                # Update checkSum  
                CheckSum += ((SegmentAddress >> 24) & 0xFF);
                CheckSum += ((SegmentAddress >> 16) & 0xFF);
                CheckSum += ((SegmentAddress >> 8)  & 0xFF);
                CheckSum += ((SegmentAddress >> 0)  & 0xFF)
                StartRecordIndex += START_SEGMENT_ADDRESS_ERROR  # Update Start Record Address
        
        elif RecordType == RECORD_TYPE_EXTENDED_LINEAR_ADDRESS:
                
                if ByteCount != 2: # the byte count for this mode is always 2
                    ErrorState = EXTENDED_LINEAR_ADDRESS_ERROR
                    return ErrorState

                # get the upper 16 bit of the address
                StartAddress   = int(OneLine[StartRecordIndex:StartRecordIndex + EXTENDED_LINEAR_ADDRESS_RECORD_SIZE], HEX_CONVERTER)
                # Update checkSum  
                CheckSum += ((StartAddress >> 8) & 0xFF);
                CheckSum += ((StartAddress >> 0) & 0xFF);
                FlashStartAddress = StartAddress   << 16
                StartRecordIndex += EXTENDED_LINEAR_ADDRESS_RECORD_SIZE # Update Start Record Address

        elif RecordType == RECORD_TYPE_START_LINEAR_ADDRESS:
            if ByteCount != 4: # the byte count for this mode is always 4
                ErrorState = START_LINEAR_ADDRESS_ERROR
                return ErrorState
            
            # get the upper 16 bit of the address
            StartLinearAddress = int(OneLine[StartRecordIndex:StartRecordIndex + START_LINEAR_ADDRESS_RECORD_SIZE], HEX_CONVERTER)
            # Update checkSum  
            CheckSum += ((StartLinearAddress >> 24) & 0xFF)
            CheckSum += ((StartLinearAddress >> 16) & 0xFF)
            CheckSum += ((StartLinearAddress >> 8)  & 0xFF)
            CheckSum += ((StartLinearAddress >> 0)  & 0xFF)
            StartRecordIndex += START_LINEAR_ADDRESS_RECORD_SIZE # Update Start Record Address

        CheckSum += int(OneLine[StartRecordIndex:StartRecordIndex + CHECK_SUM_SIZE], HEX_CONVERTER);
        if (CheckSum & 0xFF) != 0:
            ErrorState = CHECK_SUM_ERROR
            return ErrorState
        StartRecordIndex += CHECK_SUM_SIZE # Update Start Record Address

    return ErrorState, ParsedData

Parsing()