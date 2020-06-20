//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/engine/notifier.hpp"
#include "beetree/services/i-reflexes-service.hpp"

namespace bte {
///
/// A simple implementation of the reflexes service interface
/// @see IReflexesService
///
class SimpleReflexesService : public IReflexesService
{
public:
    SimpleReflexesService(ReflexesModel& model);

    ///
    /// Configure a listener to notify when a reflex has been activated
    ///
    /// @param listening_tree
    ///
    void configure_listener(IReflexesService::Listener& listening_tree);
    void configure_listener(Notifier tree_notifier);

    const ReflexesModel& model() const override;

    void enable() override;
    void disable() override;
    void activate_reflex(const Reflex& reflex) override;
    void deactivate_all_reflexes() override;

private:
    ///
    /// The internal listener used to switch between the generic listener
    /// listener and the tree notifier.  This allows unit testing of the
    /// signalling since the generic listener can be used instead of the
    /// tree notifier which is hard wired to the engine.
    ///
    struct InternalListener : public IReflexesService::Listener
    {
        Notifier tree_notifier;
        void     on_reflex_activated(Reflex reflex) override;
        // not implementing - void on_all_reflexes_deactivated()
    };

    ReflexesModel*              m_model    = nullptr;
    IReflexesService::Listener* m_listener = nullptr;
    InternalListener            m_internal_listener;
};
}  // namespace bte