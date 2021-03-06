#ifndef __ImageProvider_includes_h__
#define __ImageProvider_includes_h__

#ifdef __cplusplus
#include <direct/Types++.h>

extern "C" {
#endif


#include <fusion/types.h>
#include <fusion/lock.h>
#include <fusion/object.h>

#include <core/CoreDFB_includes.h>

#include <directfb.h>


/*
 * Image Provider client object
 */
typedef struct {
     FusionCall              call; /* copy of FusionCall from server object, using fusion_call_init_from() */
} ImageProvider;

/*
 * Image Provider server object
 */
typedef struct {
     int                     magic;

     FusionCall              call;

     IDirectFB              *idirectfb;
     IDirectFBDataBuffer    *buffer;
     IDirectFBImageProvider *provider;

     CoreResourceCleanup    *cleanup;
} ImageProviderDispatch;

DFBResult ImageProviderDispatch_Create ( IDirectFB               *idirectfb,
                                         IDirectFBDataBuffer     *buffer,
                                         IDirectFBImageProvider  *provider,
                                         ImageProviderDispatch  **ret_dispatch );

void      ImageProviderDispatch_Destroy( ImageProviderDispatch   *dispatch );


static __inline__ DirectResult
ImageProvider_Call( ImageProvider       *provider,
                    FusionCallExecFlags  flags,
                    int                  call_arg,
                    void                *ptr,
                    unsigned int         length,
                    void                *ret_ptr,
                    unsigned int         ret_size,
                    unsigned int        *ret_length )
{
     return fusion_call_execute3( &provider->call,
                                  (FusionCallExecFlags)(dfb_config->call_nodirect | flags),
                                  call_arg, ptr, length, ret_ptr, ret_size, ret_length );
}


#ifdef __cplusplus
}
#endif


#endif

