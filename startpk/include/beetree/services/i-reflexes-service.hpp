//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/models/data/reflex.hpp"
#include "beetree/models/reflexes-model.hpp"

namespace bte {
///
/// The Reflexes Service interface allows a 'reflex' tree to signal when a
/// reflex is active or deactivated.
///
/// To implement this capability, the producing tree, e.g. the reflex tree,
/// calls the signalling methods when entering/exiting a reflex behavior,
/// respectively.
///
/// In the consuming tree, e.g. the behaviors tree, the tree must subscribe
/// or listen to the signals and then invoke an exception on the behavior
/// tree.
///
/// The methods to listen and invoke the exception are dependent on the
/// implementation of the reflexes service and behaviors tree.
///
class IReflexesService
{
public:
    ///
    /// @return the model or data driving reflex activation/deactivation
    ///
    virtual const ReflexesModel& model() const = 0;
    ///
    /// Enables the reflex system allowing reflexes to be activated and
    /// signalled
    ///
    virtual void enable() = 0;
    ///
    /// Disables the reflex system and therefore does not allow any reflexes
    /// to be activated and signalled
    ///
    virtual void disable() = 0;
    ///
    /// Activates the reflex and signals the event to any interrested
    /// trees/listeners.
    ///
    /// @param reflex the activated reflex
    ///
    virtual void activate_reflex(const Reflex& reflex) = 0;
    ///
    /// Deactivates any reflexes and signals the event that all reflexes are
    /// deactivated. This will only occur if there are any active reflexes.
    /// Otherwise, nothing will occur and no listeners are signaled.
    ///
    virtual void deactivate_all_reflexes() = 0;

    ///
    /// Listener interface to support activate_reflex and
    /// deactivate_all_reflexes. It is up to the implementation to define how
    /// the listeners are utilized.
    ///
    class Listener
    {
    public:
        virtual void on_reflex_activated(Reflex reflex){};
        virtual void on_all_reflexes_deactivated(){};

        //-----------------------------------
        Listener()                = default;
        virtual ~Listener()       = default;
        Listener(const Listener&) = delete;
        Listener(Listener&&)      = delete;
        Listener& operator=(const Listener&) = delete;
        Listener& operator=(Listener&&) = delete;
    };

    //-----------------------------------
    IReflexesService()                        = default;
    virtual ~IReflexesService()               = default;
    IReflexesService(const IReflexesService&) = delete;
    IReflexesService(IReflexesService&&)      = delete;
    IReflexesService& operator=(const IReflexesService&) = delete;
    IReflexesService& operator=(IReflexesService&&) = delete;
};
}  // namespace bte