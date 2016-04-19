//
//  GSCall.h
//  Gossip
//
//  Created by Chakrit Wichian on 7/9/12.
//

#import <Foundation/Foundation.h>
#import "GSAccount.h"
#import "GSRingback.h"


/// Call session states.
typedef enum {
    GSCallStatusReady, ///< Call is ready to be made/pickup.
    GSCallStatusCalling, ///< Call is ringing.
    GSCallStatusConnecting, ///< User or other party has pick up the call.
    GSCallStatusConnected, ///< Call has connected and sound is now coming through.
    GSCallStatusDisconnected, ///< Call has been disconnected (user hangup/other party hangup.)
} GSCallStatus;


// TODO: Video call support?
/// Represents a single calling session (either incoming or outgoing.)
@interface GSCall : NSObject

@property (nonatomic, unsafe_unretained, readonly) GSAccount *account; ///< An account this call is being made from.
@property (nonatomic, readonly) GSRingback *ringback; ///< Returns the current GSRingback instance used to play the call's ringback.

@property (nonatomic, readonly) int callId; ///< Call id. Autogenerated from PJSIP.
@property (nonatomic, readonly) GSCallStatus status; ///<  Call status. Supports KVO notification.

@property (nonatomic, readonly) float volume; ///< Call volume. Set to 0 to mute.
@property (nonatomic, readonly) float micVolume; ///< Call microphone volume. i.e. the volume to transmit sound from the mic. Set to 0 to mute.

/// Creats a new outgoing call to the specified remoteUri.
/** Use begin() to begin calling. */
+ (id)outgoingCallToUri:(NSString *)remoteUri fromAccount:(GSAccount *)account;

/// Creates a new incoming call from the specified PJSIP call id. And associate it with the speicifed account.
/** Do not call this method directly, implement GSAccountDelegate and listen to the
 *  GSAccountDelegate::account:didReceiveIncomingCall: message instead. */
+ (id)incomingCallWithId:(int)callId toAccount:(GSAccount *)account;

/// Initialize a new call with the specified account.
/** Do not initialize a GSCall instance directly, instead use one of the provided static methods.
 *  This method is only inteded to be used by child classes. */
- (id)initWithAccount:(GSAccount *)account;

- (BOOL)setVolume:(float)volume; ///< Sets the call volume. Returns YES if successful.
- (BOOL)setMicVolume:(float)volume; ///< Sets the microphone volume. Returns YES if successful.

- (BOOL)begin; ///< Begins calling for outgoing call or answer incoming call.
- (BOOL)end; ///< Stop calling and/or hangup call.

- (BOOL)sendDTMFDigits:(NSString *)digits; ///< Sends DTMF digits over the call.
- (NSString*)getRemoteUri; ///< Get the remote uri address of the call.

@end
