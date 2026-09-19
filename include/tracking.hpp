#pragma once

#include <cstdint>

namespace demo {

/**
 * @brief Correlator outputs for one tracking epoch.
 *
 * The values are magnitudes of the Early, Prompt, and Late correlators.
 * Ownership stays with the caller because the structure is passed by value.
 */
struct Correlation {
    float early;
    float prompt;
    float late;
};

/**
 * @brief High-level state of one satellite tracking channel.
 */
enum class TrackingState : std::uint8_t {
    Acquiring,
    Tracking,
    Lost,
};

/**
 * @brief Maintains the code-tracking loop for one signal channel.
 *
 * One instance owns the state for exactly one tracked signal.
 * Call initialize() once, then call update() once per 1 ms epoch.
 *
 * @par Thread safety
 * This class is not thread-safe. All calls for one instance must come from
 * the same tracking task.
 *
 * @see tracking_loop
 */
class TrackingLoop {
public:
    /**
     * @brief Initializes the tracking loop before the first update.
     *
     * @param initial_code_phase Initial code phase in chips.
     * @param initial_doppler_hz Initial carrier Doppler estimate in hertz.
     *
     * @post state() returns TrackingState::Tracking.
     * @see tracking_loop
     */
    void initialize(float initial_code_phase, float initial_doppler_hz);

    /**
     * @brief Advances the tracking loop by one 1 ms epoch.
     *
     * The function computes a normalized Early-minus-Late discriminator and
     * applies it to the loop filter described on @ref tracking_loop.
     *
     * @param correlation Early, Prompt, and Late correlator magnitudes.
     * @return Normalized DLL error. Positive values move the local code phase
     *         toward Early; negative values move it toward Late.
     *
     * @pre initialize() has completed successfully.
     * @note This function performs no dynamic allocation.
     * @warning Do not call this function from two tasks concurrently.
     */
    float update(Correlation correlation);

    /**
     * @brief Returns the current tracking state.
     */
    [[nodiscard]] TrackingState state() const noexcept;

private:
    TrackingState state_{TrackingState::Acquiring};
    float code_phase_chips_{0.0F};
    float carrier_doppler_hz_{0.0F};
};

}  // namespace demo
