/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file system_event_manager.h
 * @date 2021-10-03
 * 
 * @copyright Copyright (c) 2021
 */

#ifndef SYSTEM_EVENT_MANAGER_H
#define SYSTEM_EVENT_MANAGER_H

#include "listener_notifier.h"
#include "system_events.h"

namespace Sml
{
    class SystemEventManager : public Notifier
    {
    public:
        //--------------------------------------------------------------------------
        //! @brief Proccess all events currently in the event queue. Notify
        //!        listeners of them.
        //--------------------------------------------------------------------------
        void proccessEvents();

        //--------------------------------------------------------------------------
        //! @brief Polls for currently pending events. The next event is removed
        //!        from the queue and returned.
        //! 
        //! @warning The returned event is allocated dynamically and should be
        //!          deleted with @code delete @endcode after usage!
        //! 
        //! @param notifyListeners Indicates whether to notify listeners of the
        //!                        event or not.
        //! 
        //! @return The next event in the queue or nullptr, if there are no pending
        //!         events.
        //--------------------------------------------------------------------------
        Event* pollEvent(bool notifyListeners = false);
    };
}

#endif // SYSTEM_EVENT_MANAGER_H