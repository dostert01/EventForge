#include "mqttlistener.h"
#include "applicationcontext.h"

using namespace std;
using namespace event_forge;

MQTTListener::MQTTListener(json jsonObject) {
  hostName = jsonObject["hostName"];
  port = jsonObject["port"];
  clientId = jsonObject["clientId"];
  topics = APP_CONTEXT.createObjectsFromJson<MQTTTopic>(jsonObject, "topics");
};

shared_ptr<MQTTListener> MQTTListener::getInstance() {
  return make_shared<MQTTListener>();
}

void MQTTListener::init(shared_ptr<PipelineFiFo> fifo) {
    NetworkListener::init(fifo);
    MosquittoWrapper::getInstance(hostName, port, clientId, getTopicNames());
    mqtt = MosquittoWrapper::getInstance(hostName, port, clientId, getTopicNames());
    initComplete = mqtt->isInitComplete();
}

void MQTTListener::startListening() {
    mqtt->startListening(pipelineFifo);
    setIsListening(mqtt->isListening());
}

string MQTTListener::getHostName() {
    return hostName;
}

int MQTTListener::getPort() {
    return port;
}

string MQTTListener::getClientId() {
    return clientId;
}

optional<string> MQTTListener::getTopic(int index) {
    if((index > -1) && (index < topics.size())) {
        return topics[index].get()->getName();
    } else {
        return nullopt;
    }
}

vector<string> MQTTListener::getTopicNames() {
    vector<string> returnValue;
    for(auto topic : topics) {
        returnValue.push_back(topic.get()->getName());
    }
    return returnValue;
}

// ----------------------------------------------------------------------------
MQTTTopic::MQTTTopic(json jsonObject) {
  name = jsonObject["name"];
}

string MQTTTopic::getName() {
  return name;
}
