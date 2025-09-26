#ifndef POST_STATE_PROCESSOR_H
#define POST_STATE_PROCESSOR_H

class SimulationState;

class PostStateProcessor {
public:
    PostStateProcessor(){};
    ~PostStateProcessor(){};
    virtual double computeMetric(const SimulationState& state) const = 0;  // computes metric and passes to recorder

};


class gridMSDProcessor : public PostStateProcessor {
    public:
        double computeMetric(const SimulationState& state) const override;
};

class walkerMSDProcessor : public PostStateProcessor {
    public:
        double computeMetric(const SimulationState& state) const override;
};


#endif