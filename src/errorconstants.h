/**************************************************************************
    Lightspark, a free flash player implementation

    Copyright (C) 2013  Alessandro Pignotti (a.pignotti@sssup.it)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/

/* This file is generated by errorgen - DO NOT EDIT */

#ifndef ERRORCONSTANTS_H
#define ERRORCONSTANTS_H 1

#include <map>

namespace lightspark
{

enum
{
	kOutOfMemoryError                       = 1000,
	kNotImplementedError                    = 1001,
	kInvalidPrecisionError                  = 1002,
	kInvalidRadixError                      = 1003,
	kInvokeOnIncompatibleObjectError        = 1004,
	kArrayIndexNotIntegerError              = 1005,
	kCallOfNonFunctionError                 = 1006,
	kConstructOfNonFunctionError            = 1007,
	kAmbiguousBindingError                  = 1008,
	kConvertNullToObjectError               = 1009,
	kConvertUndefinedToObjectError          = 1010,
	kIllegalOpcodeError                     = 1011,
	kLastInstExceedsCodeSizeError           = 1012,
	kFindVarWithNoScopeError                = 1013,
	kClassNotFoundError                     = 1014,
	kIllegalSetDxns                         = 1015,
	kDescendentsError                       = 1016,
	kScopeStackOverflowError                = 1017,
	kScopeStackUnderflowError               = 1018,
	kGetScopeObjectBoundsError              = 1019,
	kCannotFallOffMethodError               = 1020,
	kInvalidBranchTargetError               = 1021,
	kIllegalVoidError                       = 1022,
	kStackOverflowError                     = 1023,
	kStackUnderflowError                    = 1024,
	kInvalidRegisterError                   = 1025,
	kSlotExceedsCountError                  = 1026,
	kMethodInfoExceedsCountError            = 1027,
	kDispIdExceedsCountError                = 1028,
	kDispIdUndefinedError                   = 1029,
	kStackDepthUnbalancedError              = 1030,
	kScopeDepthUnbalancedError              = 1031,
	kCpoolIndexRangeError                   = 1032,
	kCpoolEntryWrongTypeError               = 1033,
	kCheckTypeFailedError                   = 1034,
	kIllegalSuperCallError                  = 1035,
	kCannotAssignToMethodError              = 1037,
	kRedefinedError                         = 1038,
	kCannotVerifyUntilReferencedError       = 1039,
	kCantUseInstanceofOnNonObjectError      = 1040,
	kIsTypeMustBeClassError                 = 1041,
	kInvalidMagicError                      = 1042,
	kInvalidCodeLengthError                 = 1043,
	kInvalidMethodInfoFlagsError            = 1044,
	kUnsupportedTraitsKindError             = 1045,
	kMethodInfoOrderError                   = 1046,
	kMissingEntryPointError                 = 1047,
	kPrototypeTypeError                     = 1049,
	kConvertToPrimitiveError                = 1050,
	kIllegalEarlyBindingError               = 1051,
	kInvalidURIError                        = 1052,
	kIllegalOverrideError                   = 1053,
	kIllegalExceptionHandlerError           = 1054,
	kWriteSealedError                       = 1056,
	kIllegalSlotError                       = 1057,
	kIllegalOperandTypeError                = 1058,
	kClassInfoOrderError                    = 1059,
	kClassInfoExceedsCountError             = 1060,
	kNumberOutOfRangeError                  = 1061,
	kWrongArgumentCountError                = 1063,
	kCannotCallMethodAsConstructor          = 1064,
	kUndefinedVarError                      = 1065,
	kFunctionConstructorError               = 1066,
	kIllegalNativeMethodBodyError           = 1067,
	kCannotMergeTypesError                  = 1068,
	kReadSealedError                        = 1069,
	kCallNotFoundError                      = 1070,
	kAlreadyBoundError                      = 1071,
	kZeroDispIdError                        = 1072,
	kDuplicateDispIdError                   = 1073,
	kConstWriteError                        = 1074,
	kMathNotFunctionError                   = 1075,
	kMathNotConstructorError                = 1076,
	kWriteOnlyError                         = 1077,
	kIllegalOpMultinameError                = 1078,
	kIllegalNativeMethodError               = 1079,
	kIllegalNamespaceError                  = 1080,
	kReadSealedErrorNs                      = 1081,
	kNoDefaultNamespaceError                = 1082,
	kXMLPrefixNotBound                      = 1083,
	kXMLBadQName                            = 1084,
	kXMLUnterminatedElementTag              = 1085,
	kXMLOnlyWorksWithOneItemLists           = 1086,
	kXMLAssignmentToIndexedXMLNotAllowed    = 1087,
	kXMLMarkupMustBeWellFormed              = 1088,
	kXMLAssigmentOneItemLists               = 1089,
	kXMLMalformedElement                    = 1090,
	kXMLUnterminatedCData                   = 1091,
	kXMLUnterminatedXMLDecl                 = 1092,
	kXMLUnterminatedDocTypeDecl             = 1093,
	kXMLUnterminatedComment                 = 1094,
	kXMLUnterminatedAttribute               = 1095,
	kXMLUnterminatedElement                 = 1096,
	kXMLUnterminatedProcessingInstruction   = 1097,
	kXMLNamespaceWithPrefixAndNoURI         = 1098,
	kRegExpFlagsArgumentError               = 1100,
	kNoScopeError                           = 1101,
	kIllegalDefaultValue                    = 1102,
	kCannotExtendFinalClass                 = 1103,
	kXMLDuplicateAttribute                  = 1104,
	kCorruptABCError                        = 1107,
	kInvalidBaseClassError                  = 1108,
	kDanglingFunctionError                  = 1109,
	kCannotExtendError                      = 1110,
	kCannotImplementError                   = 1111,
	kCoerceArgumentCountError               = 1112,
	kInvalidNewActivationError              = 1113,
	kNoGlobalScopeError                     = 1114,
	kNotConstructorError                    = 1115,
	kApplyError                             = 1116,
	kXMLInvalidName                         = 1117,
	kXMLIllegalCyclicalLoop                 = 1118,
	kDeleteTypeError                        = 1119,
	kDeleteSealedError                      = 1120,
	kDuplicateMethodBodyError               = 1121,
	kIllegalInterfaceMethodBodyError        = 1122,
	kFilterError                            = 1123,
	kInvalidHasNextError                    = 1124,
	kOutOfRangeError                        = 1125,
	kVectorFixedError                       = 1126,
	kTypeAppOfNonParamType                  = 1127,
	kWrongTypeArgCountError                 = 1128,
	kJSONCyclicStructure                    = 1129,
	kJSONInvalidReplacer                    = 1131,
	kJSONInvalidParseInput                  = 1132,
	kFileOpenError                          = 1500,
	kFileWriteError                         = 1501,
	kScriptTimeoutError                     = 1502,
	kScriptTerminatedError                  = 1503,
	kEndOfFileError                         = 1504,
	kStringIndexOutOfBoundsError            = 1505,
	kInvalidRangeError                      = 1506,
	kNullArgumentError                      = 1507,
	kInvalidArgumentError                   = 1508,
	kArrayFilterNonNullObjectError          = 1510,
	kWorkerAlreadyStarted                   = 1511,
	kFailedWorkerCannotBeRestarted          = 1512,
	kWorkerTerminated                       = 1513,
	kMutextNotLocked                        = 1514,
	kConditionInvalidTimeout                = 1515,
	kConditionCannotNotify                  = 1516,
	kConditionCannotNotifyAll               = 1517,
	kConditionCannotWait                    = 1518,
	kConditionCannotBeInitialized           = 1519,
	kMutexCannotBeInitialized               = 1520,
	kWorkerIllegalCallToStart               = 1521,
	kInvalidSocket                          = 2002,
	kInvalidParamError                      = 2004,
	kParamRangeError                        = 2006,
	kNullPointerError                       = 2007,
	kInvalidEnumError                       = 2008,
	kCantInstantiateError                   = 2012,
	kInvalidBitmapData                      = 2015,
	kParamRangeNonNegativeError             = 2027,
	kEOFError                               = 2030,
	kCompressedDataError                    = 2058,
	kEmptyStringError                       = 2085,
	kProxyGetPropertyError                  = 2088,
	kProxySetPropertyError                  = 2089,
	kProxyCallPropertyError                 = 2090,
	kProxyHasPropertyError                  = 2091,
	kProxyDeletePropertyError               = 2092,
	kProxyGetDescendantsError               = 2093,
	kProxyNextNameIndexError                = 2105,
	kProxyNextNameError                     = 2106,
	kProxyNextValueError                    = 2107,
	kInvalidArrayLengthError                = 2108,
	kReadExternalNotImplementedError        = 2173,
};

extern const std::map<int, const char *> errorMessages;

};

#endif /* ERRORCONSTANTS_H */
