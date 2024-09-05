#ifndef SECOND_TAKE_PIPELINE
#define SECOND_TAKE_PIPELINE

#include <memory>
#include <optional>
#include <vector>
#include <nlohmann/json.hpp>

#include "pipelineapi.h"

using json = nlohmann::json;

namespace second_take {

class PipelineException : public std::exception {
    public:
        explicit PipelineException(const std::string& message);
        //virtual const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW  noexcept override;
        virtual const char* what() const noexcept override;
    private:
        std::string message;
}; 

using LibInitFunction = int (*)(LibInitData* initData);
using LibProcessFunction = int (*)(LibProcessingData& initData);
using LibFinishFunction = int (*)();

class PipelineStep {
    public:
        PipelineStep() = default;
        ~PipelineStep();
        void setStepName(const std::string stepName);
        std::string getStepName();
        void setLibraryName(const std::string libraryName);
        bool isInitComplete();
        void runInitFunction();
        void runProcessFunction();
        void runFinishFunction();
        void loadLib();
        void loadNamedArguments(const json& jsonData);
    private:
        std::string stepName;
        std::string libraryName;
        void *hLib;
        LibInitFunction libInit;
        LibProcessFunction libProcess;
        LibFinishFunction libFinish;
        LibInitData initData;
        LibProcessingData processData;
};

class Pipeline {
    public:
        Pipeline() = default;
        static std::unique_ptr<Pipeline> getInstance();
        static std::optional<std::unique_ptr<Pipeline>> getInstance(const std::string configFilePath);
        uint getCountOfPipelineSteps();
        std::optional<PipelineStep*> getStepByName(const std::string& stepName);
        void setPipelineName(const std::string& pipelineName);
        std::string getPipelineName();
        void execute();
    private:
        std::string pipelineName;
        std::vector<std::unique_ptr<PipelineStep>> pipelineSteps;
        void loadPipelineConfig(const std::string& configFilePath);
        void loadPipelineMetaData(const json& jsonData);
        void loadPipelineSteps(const json& jsonData);
};

}

#endif // SECOND_TAKE_PIPELINE