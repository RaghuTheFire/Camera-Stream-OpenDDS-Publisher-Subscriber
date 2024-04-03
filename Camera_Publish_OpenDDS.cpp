#include <dds/pub/Publisher.hpp>
#include <dds/pub/DataWriter.hpp>
#include <dds/topic/Topic.hpp>

int main() 
{
  // Initialize OpenCV video capture
  cv::VideoCapture cap(0);
  if (!cap.isOpened()) 
  {
    std::cerr << "Failed to open video capture device" << std::endl;
    return 1;
  }

  // Initialize OpenSplice DDS
  dds::domain::DomainParticipant participant(0);
  dds::pub::Publisher publisher(participant);
  dds::topic::Topic < cv::Mat > topic(participant, "VideoFrame");
  dds::pub::DataWriter < cv::Mat > writer(publisher, topic);

  while (true) 
  {
    // Capture a frame from the video
    cv::Mat frame;
    cap >> frame;

    // Publish the frame using OpenSplice DDS
    writer.write(frame);
  }

  return 0;
}
