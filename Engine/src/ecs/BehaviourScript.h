#pragma once
namespace eng
{
	class BehaviourScript
	{
	public:
		virtual void OnInit() {}
		virtual void OnUpdate() {}
		virtual void OnDestroy() {}

		const Entity GetAttachedEntity() const { return id; }

	protected:
		//wrappers for convinient scripting
		template<typename T>
		T& GetComponent() const
		{
			return id.GetComponent<T>();
		}
		template<typename T>
		bool HasComponent() const
		{
			return id.HasComponent();
		}
		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			return id.AddComponent<T>(args);
		}
		template<typename T>
		void RemoveComponent()
		{
			Logger::Log(id);
			id.RemoveComponent<T>();
		}
	private:
		Entity id;
		friend class Scene;
	};
}