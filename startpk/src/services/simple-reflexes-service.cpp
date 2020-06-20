#include "beetree/services/simple-reflexes-service.hpp"
#include "beetree/btos/flags.hpp"
#include "beetree/startpk/tokens.hpp"

namespace bte {
using Listener = IReflexesService::Listener;

SimpleReflexesService::SimpleReflexesService(ReflexesModel& model) : m_model(&model) {}

void SimpleReflexesService::configure_listener(Listener& listening_tree)
{
    m_listener = &listening_tree;
}

void SimpleReflexesService::configure_listener(Notifier tree_notifier)
{
    m_internal_listener.tree_notifier = tree_notifier;
    m_listener                        = &m_internal_listener;
}

const ReflexesModel& SimpleReflexesService::model() const { return *m_model; }

void SimpleReflexesService::enable() { m_model->is_enabled = true; }
void SimpleReflexesService::disable() { m_model->is_enabled = false; }

void SimpleReflexesService::activate_reflex(const Reflex& reflex)
{
    if (m_model->is_enabled)
    {
        flags::set(m_model->current_reflexes, reflex);

        // signal the engine by injecting a reflex exception
        if (m_listener) m_listener->on_reflex_activated(reflex);

        trace::info(tokens::ReflexActivated) << static_cast<uint32_t>(reflex.value);
    }
}

void SimpleReflexesService::deactivate_all_reflexes()
{
    // only signal if any reflexes are active.
    if (flags::any(m_model->current_reflexes))
    {
        // reset the model
        flags::reset(m_model->current_reflexes);

        // inform the listeners
        if (m_listener) m_listener->on_all_reflexes_deactivated();
        // trace it
        trace::info(tokens::ReflexesDeactivated);
    }
}

void SimpleReflexesService::InternalListener::on_reflex_activated(Reflex reflex)
{
    tree_notifier.raise(ReflexException(reflex.value));
}
}  // namespace bte