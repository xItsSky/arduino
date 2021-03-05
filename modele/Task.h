public enum class TaskState {
	Todo, InProgress, Done;
};

public class Task {
	private:
		char* id;
		TaskState state;
	public:
		char* getId();
		TaskState getState();
};