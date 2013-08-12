#define NakamapIDDidSet             @"NakamapIDDidSet"
#define NakamapEncryptedIDDidSend   @"NakamapEncryptedIDDidSend"

// deprecated notification name
#define NakamapViewWillAppear       @"NakamapViewWillAppear"
#define NakamapViewDidAppear        @"NakamapViewDidAppear"
#define NakamapViewWillDisappear    @"NakamapViewWillDisappear"
#define NakamapViewDidDisappear     @"NakamapViewDidDisappear"

typedef enum {
    NKAPIStatusCodeSuccess       = 0,
    NKAPIStatusCodeNetworkError  = 100,
    NKAPIStatusCodeResponseError = 101,
    NKAPIStatusCodeFatalError    = 102
} NKAPIStatusCode;

typedef enum {
    NKHTTPMethodGET = 0,
    NKHTTPMethodPOST
} NKHTTPMethod;

typedef enum {
    NKPermissionTypeAnyUser = 0,
    NKPermissionTypeLeader,
    NKPermissionTypeSuperUser,
} NKPermissionType;

typedef enum {
    NKNakamapPageTypeIndex = 0,
    NKNakamapPageTypeSetting,
    NKNakamapPageTypeAccount,
} NKNakamapPageType;

