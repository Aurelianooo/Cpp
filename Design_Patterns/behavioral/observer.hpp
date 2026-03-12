/**
 * Observer Design Pattern
 *
 * Intent: Lets you define a subscription mechanism to notify multiple objects
 * about any events that happen to the object they're observing.
 *
 * Note that there's a lot of different terms with similar meaning associated
 * with this pattern. Just remember that the Subject is also called the
 * Publisher and the Observer is often called the Subscriber and vice versa.
 * Also the verbs "observe", "listen" or "track" usually mean the same thing.
 */

 #include <iostream>
 #include <list>
 #include <string>
 
 class IObserver
 {
 public:
     virtual ~IObserver() {};
     virtual void Update(const std::string &message_from_subject) = 0;
 };
 
 class ISubject
 {
 public:
     virtual ~ISubject() {};
     virtual void Attach(IObserver *observer) = 0;
     virtual void Detach(IObserver *observer) = 0;
     virtual void Notify() = 0;
 };
 