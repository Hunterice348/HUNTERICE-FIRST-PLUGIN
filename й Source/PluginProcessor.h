#pragma once

#include <JuceHeader.h>

class HuntericeFirstPluginAudioProcessor : public juce::AudioProcessor
{
public:
    HuntericeFirstPluginAudioProcessor();
    ~HuntericeFirstPluginAudioProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState& getAPVTS() { return apvts; }

private:
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    juce::AudioProcessorValueTreeState apvts;

    // Smoothed values для избежания щелчков при изменении параметров
    juce::LinearSmoothedValue<float> driveSmoothed;
    juce::LinearSmoothedValue<float> mixSmoothed;
    juce::LinearSmoothedValue<float> outputSmoothed;

    // Указатели на параметры (кэшируем для быстрого доступа в аудиопотоке)
    std::atomic<float>* driveParamRaw { nullptr };
    std::atomic<float>* mixParamRaw { nullptr };
    std::atomic<float>* outputParamRaw { nullptr };

    // Distortion алгоритм (soft clipping через tanh)
    static inline float applyDistortion(float sample, float drive) noexcept;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HuntericeFirstPluginAudioProcessor)
};
