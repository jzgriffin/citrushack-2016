TARGET = CitrusHack2016
TEMPLATE = app
QT += core gui widgets
CONFIG += c++11

SOURCES += \
    Keypad.cpp \
    MainWindow.cpp \
    VirtualMachine.cpp \
    ai/ActivatorSet.cpp \
    ai/Activators.cpp \
    ai/Genome.cpp \
    ai/Innovator.cpp \
    ai/Network.cpp \
    ai/NeuronGene.cpp \
    ai/SynapseGene.cpp \
    main.cpp
HEADERS += \
    Keypad.hpp \
    MainWindow.hpp \
    VirtualMachine.hpp \
    ai/Activator.hpp \
    ai/ActivatorSet.hpp \
    ai/Activators.hpp \
    ai/Configuration.hpp \
    ai/Genome.hpp \
    ai/Innovator.hpp \
    ai/Network.hpp \
    ai/Neuron.hpp \
    ai/NeuronGene.hpp \
    ai/Random.hpp \
    ai/Real.hpp \
    ai/Synapse.hpp \
    ai/SynapseGene.hpp
FORMS += \
    MainWindow.ui
