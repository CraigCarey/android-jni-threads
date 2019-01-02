#include <jni.h>
#include <string>
#include <thread>

long duration1 = 0;
long duration2 = 0;

void func1()
{
	auto start = std::chrono::high_resolution_clock::now();

	std::chrono::milliseconds timespan(1500);
	std::this_thread::sleep_for(timespan);

	auto end = std::chrono::high_resolution_clock::now();
	duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

void func2()
{
	auto start = std::chrono::high_resolution_clock::now();

	std::chrono::milliseconds timespan(2000);
	std::this_thread::sleep_for(timespan);

	auto end = std::chrono::high_resolution_clock::now();
	duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_craig_hellojni_MainActivity_stringFromJNI(
		JNIEnv *env,
		jobject /* this */)
{
	auto start = std::chrono::high_resolution_clock::now();

	std::thread t1(func1);
	std::thread t2(func2);

	t1.join();
	t2.join();

	auto end = std::chrono::high_resolution_clock::now();

	long tot_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

	std::string hello = "D1: " + std::to_string(duration1)
			+ "\nD2: " + std::to_string(duration2)
			+ "\nDT: " + std::to_string(tot_duration);
	return env->NewStringUTF(hello.c_str());
}
