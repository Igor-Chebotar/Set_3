import pandas as pd
import matplotlib.pyplot as plt
import matplotlib

def smooth_data(df, window=20):
    """Сглаживание данных скользящим средним"""
    df_smooth = df.copy()
    df_smooth['time_us'] = df['time_us'].rolling(window=window, center=True, min_periods=1).mean()
    return df_smooth

def calculate_improvement(merge_data, hybrid_data):
    merge_time = merge_data[merge_data['size'] == 100000]['time_us'].values[0]
    hybrid_time = hybrid_data[hybrid_data['size'] == 100000]['time_us'].values[0]
    improvement = ((merge_time - hybrid_time) / merge_time) * 100
    return merge_time, hybrid_time, improvement


matplotlib.use('Agg')

# Настройка шрифтов для кириллицы
plt.rcParams['font.family'] = 'DejaVu Sans'
plt.rcParams['axes.unicode_minus'] = False


print("Чтение данных из CSV файлов")

random_merge = pd.read_csv('data/random_merge.csv')
random_hybrid = pd.read_csv('data/random_hybrid.csv')

reversed_merge = pd.read_csv('data/reversed_merge.csv')
reversed_hybrid = pd.read_csv('data/reversed_hybrid.csv')

nearly_sorted_merge = pd.read_csv('data/nearly_sorted_merge.csv')
nearly_sorted_hybrid = pd.read_csv('data/nearly_sorted_hybrid.csv')

print("Данные загружены успешно!\n")

# Сглаживаем данные
random_merge_smooth = smooth_data(random_merge)
random_hybrid_smooth = smooth_data(random_hybrid)

reversed_merge_smooth = smooth_data(reversed_merge)
reversed_hybrid_smooth = smooth_data(reversed_hybrid)

nearly_sorted_merge_smooth = smooth_data(nearly_sorted_merge)
nearly_sorted_hybrid_smooth = smooth_data(nearly_sorted_hybrid)


# Случайные
plt.figure(figsize=(12, 7))

plt.plot(random_merge_smooth['size'], random_merge_smooth['time_us'],
         label='Merge Sort', linewidth=2.5, alpha=0.9, color='red')
plt.plot(random_hybrid_smooth['size'], random_hybrid_smooth['time_us'],
         label='Hybrid Sort (порог=15)', linewidth=2.5, alpha=0.9, color='blue')

plt.xlabel('Размер массива', fontsize=13, fontweight='bold')
plt.ylabel('Время (микросекунды)', fontsize=13, fontweight='bold')
plt.title('Сравнение на случайных массивах', fontsize=15, fontweight='bold')
plt.legend(fontsize=12, loc='upper left')
plt.grid(True, alpha=0.3, linestyle='--')
plt.tight_layout()

plt.savefig('plots/random_comparison.png', dpi=300, bbox_inches='tight')
print("График 1 сохранён: random_comparison.png")
plt.close()


# Обратно отсортированные
plt.figure(figsize=(12, 7))

plt.plot(reversed_merge_smooth['size'], reversed_merge_smooth['time_us'],
         label='Merge Sort', linewidth=2.5, alpha=0.9, color='red')
plt.plot(reversed_hybrid_smooth['size'], reversed_hybrid_smooth['time_us'],
         label='Hybrid Sort (порог=15)', linewidth=2.5, alpha=0.9, color='blue')

plt.xlabel('Размер массива', fontsize=13, fontweight='bold')
plt.ylabel('Время (микросекунды)', fontsize=13, fontweight='bold')
plt.title('Сравнение на обратно отсортированных массивах', fontsize=15, fontweight='bold')
plt.legend(fontsize=12, loc='upper left')
plt.grid(True, alpha=0.3, linestyle='--')
plt.tight_layout()

plt.savefig('plots/reversed_comparison.png', dpi=300, bbox_inches='tight')
print("График 2 сохранён: reversed_comparison.png")
plt.close()


# Почти отсортированные
plt.figure(figsize=(12, 7))

plt.plot(nearly_sorted_merge_smooth['size'], nearly_sorted_merge_smooth['time_us'],
         label='Merge Sort', linewidth=2.5, alpha=0.9, color='red')
plt.plot(nearly_sorted_hybrid_smooth['size'], nearly_sorted_hybrid_smooth['time_us'],
         label='Hybrid Sort (порог=15)', linewidth=2.5, alpha=0.9, color='blue')

plt.xlabel('Размер массива', fontsize=13, fontweight='bold')
plt.ylabel('Время (микросекунды)', fontsize=13, fontweight='bold')
plt.title('Сравнение на почти отсортированных массивах', fontsize=15, fontweight='bold')
plt.legend(fontsize=12, loc='upper left')
plt.grid(True, alpha=0.3, linestyle='--')
plt.tight_layout()

plt.savefig('plots/nearly_sorted_comparison.png', dpi=300, bbox_inches='tight')
print("График 3 сохранён: nearly_sorted_comparison.png")
plt.close()


# Все 3 типа
fig, axes = plt.subplots(3, 1, figsize=(14, 16))

# График 1: Случайные
axes[0].plot(random_merge_smooth['size'], random_merge_smooth['time_us'],
             label='Merge Sort', linewidth=2.5, alpha=0.9, color='red')
axes[0].plot(random_hybrid_smooth['size'], random_hybrid_smooth['time_us'],
             label='Hybrid Sort', linewidth=2.5, alpha=0.9, color='blue')
axes[0].set_xlabel('Размер массива', fontsize=12, fontweight='bold')
axes[0].set_ylabel('Время (микросекунды)', fontsize=12, fontweight='bold')
axes[0].set_title('Случайные массивы', fontsize=14, fontweight='bold', pad=15)
axes[0].legend(fontsize=11, loc='upper left')
axes[0].grid(True, alpha=0.3, linestyle='--')

# График 2: Обратно отсортированные
axes[1].plot(reversed_merge_smooth['size'], reversed_merge_smooth['time_us'],
             label='Merge Sort', linewidth=2.5, alpha=0.9, color='red')
axes[1].plot(reversed_hybrid_smooth['size'], reversed_hybrid_smooth['time_us'],
             label='Hybrid Sort', linewidth=2.5, alpha=0.9, color='blue')
axes[1].set_xlabel('Размер массива', fontsize=12, fontweight='bold')
axes[1].set_ylabel('Время (микросекунды)', fontsize=12, fontweight='bold')
axes[1].set_title('Обратно отсортированные массивы', fontsize=14, fontweight='bold', pad=15)
axes[1].legend(fontsize=11, loc='upper left')
axes[1].grid(True, alpha=0.3, linestyle='--')

# График 3: Почти отсортированные
axes[2].plot(nearly_sorted_merge_smooth['size'], nearly_sorted_merge_smooth['time_us'],
             label='Merge Sort', linewidth=2.5, alpha=0.9, color='red')
axes[2].plot(nearly_sorted_hybrid_smooth['size'], nearly_sorted_hybrid_smooth['time_us'],
             label='Hybrid Sort', linewidth=2.5, alpha=0.9, color='blue')
axes[2].set_xlabel('Размер массива', fontsize=12, fontweight='bold')
axes[2].set_ylabel('Время (микросекунды)', fontsize=12, fontweight='bold')
axes[2].set_title('Почти отсортированные массивы', fontsize=14, fontweight='bold', pad=15)
axes[2].legend(fontsize=11, loc='upper left')
axes[2].grid(True, alpha=0.3, linestyle='--')

plt.tight_layout()
plt.savefig('plots/all_comparison.png', dpi=300, bbox_inches='tight')
print("График 4 сохранён: all_comparison.png")
plt.close()

# Статистика
print("СТАТИСТИЧЕСКИЙ АНАЛИЗ")

print("\n--- СЛУЧАЙНЫЕ МАССИВЫ ---")
mt, ht, imp = calculate_improvement(random_merge_smooth, random_hybrid_smooth)
print(f"Merge Sort (N=100000): {mt:.2f} микросекунд")
print(f"Hybrid Sort (N=100000): {ht:.2f} микросекунд")
print(f"Улучшение: {imp:.2f}%")

print("\n--- ОБРАТНО ОТСОРТИРОВАННЫЕ МАССИВЫ ---")
mt, ht, imp = calculate_improvement(reversed_merge_smooth, reversed_hybrid_smooth)
print(f"Merge Sort (N=100000): {mt:.2f} микросекунд")
print(f"Hybrid Sort (N=100000): {ht:.2f} микросекунд")
print(f"Улучшение: {imp:.2f}%")

print("\n--- ПОЧТИ ОТСОРТИРОВАННЫЕ МАССИВЫ ---")
mt, ht, imp = calculate_improvement(nearly_sorted_merge_smooth, nearly_sorted_hybrid_smooth)
print(f"Merge Sort (N=100000): {mt:.2f} микросекунд")
print(f"Hybrid Sort (N=100000): {ht:.2f} микросекунд")
print(f"Улучшение: {imp:.2f}%")

print("Все графики успешно сохранены!")