//------------------------------------------------------------------------------
//! @author Nikita Mochalov (github.com/tralf-strues)
//! @file event_dispatching.h
//! @date 2021-10-23
//! 
//! @copyright Copyright (c) 2021
//------------------------------------------------------------------------------

#ifndef EVENT_DISPATCHING_H
#define EVENT_DISPATCHING_H

#include "event.h"

class EventDispatchChain;

class EventDispatcher
{
public:
    //--------------------------------------------------------------------------
    //! @brief Dispatches the event.
    //!
    //! Proccesses the event and/or its further path down the
    //! @ref EventDispatchChain if necessary. If the event is not consumed
    //! during the capturing phase, it is supposed to be dispatcher to the rest
    //! of the chain.
    //!
    //! @param event 
    //! @param chain Tail of the dispatch chain. Isn't supposed to change during
    //!              the whole dispatching proccess.
    //!  
    //! @return The return event or nullptr if the event has been consumed. 
    //--------------------------------------------------------------------------
    virtual Event* dispatchEvent(Event* event, EventDispatchChain* chain);
};

class EventDispatchChain
{
public:
    //--------------------------------------------------------------------------
    //! @brief Prepends the dispatcher to the chain, i.e. adds the dispatcher to
    //!        the front of the chain (before the chain's current head).
    //! 
    //! @attention The caller shouldn't assume that this @ref EventDispatchChain
    //!            remains unchanged nor that the returned chain will point to a
    //!            different chain after the call. The call look like this:
    //!            @code chain = chain.prependDispatcher(dispatcher); @endcode
    //! 
    //! @param dispatcher
    //--------------------------------------------------------------------------
    virtual void prependDispatcher(EventDispatcher* dispatcher);

    //--------------------------------------------------------------------------
    //! @brief Send the event through this chain.
    //! 
    //! The event is passed from one @ref EventDispatcher to the next in the
    //! chain until the end of the chain is reached. Each @ref EventDispatcher
    //! in the chain can change the event path and the event itself. The chain
    //! is usually formed by following some hierarchy from the root to the
    //! event target (or vice versa in the internal SGL implementation).
    //! 
    //! @param event
    //!
    //! @return The proccessed event or nullptr if the event has been consumed.
    //--------------------------------------------------------------------------
    virtual Event* sendThroughChain(Event* event);
};

class EventTarget
{
public:
    //--------------------------------------------------------------------------
    //! @brief Construct an event dispatch chain for this target.
    //!
    //! The event dispatch chain is constructed by modifications to the provided
    //! initial event dispatch chain. The returned chain should have the initial
    //! chain at its end so the dispatchers should be @b prepended to the
    //! initial chain.
    //! 
    //! @param chain The initial chain to build from.
    //!
    //! @return The resulting event dispatch chain for this target.
    //--------------------------------------------------------------------------
    virtual EventDispatchChain* buildEventDispatchChain(EventDispatchChain* chain);
};

#endif // EVENT_DISPATCHING_H