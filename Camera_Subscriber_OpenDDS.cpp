#include <iostream>
#include <dds/dds.hpp>
#include <dds/sub/Subscriber.hpp>
#include <dds/sub/DataReader.hpp>
#include <dds/sub/AnyDataReader.hpp>
#include <dds/core/types.hpp>
#include <dds/core/Time.hpp>
#include <dds/core/status/State.hpp>

int main() 
{
    // Initialize DDS
    dds::domain::DomainParticipant participant(0);

    // Create a Subscriber
    dds::sub::Subscriber subscriber(participant);

    // Create a DataReader for the video frame topic
    dds::topic::Topic<cv::Mat> topic(participant, "VideoFrameTopic");
    dds::sub::DataReader<cv::Mat> reader(subscriber, topic);

    // Wait for data
    dds::sub::LoanedSamples<cv::Mat> samples = reader.take();
    for (const auto& sample : samples) 
	{
        if (sample.info().valid()) 
		{
            // Process the video frame
            const cv::Mat& frame = sample.data();
            // Your video frame processing code goes here
        }
    }

    return 0;
}
