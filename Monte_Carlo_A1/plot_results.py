import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

wide = pd.read_csv('data/wide_area.csv')
narrow = pd.read_csv('data/narrow_area.csv')

exact_area = 0.25 * np.pi + 1.25 * np.arcsin(0.8) - 1.0

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(16, 6))

# === ЛЕВЫЙ ГРАФИК ===
ax1.plot(wide['N'], wide['area_estimate'],
         label='Широкая область', linewidth=2, alpha=0.7)
ax1.plot(narrow['N'], narrow['area_estimate'],
         label='Узкая область', linewidth=2, alpha=0.7)
ax1.axhline(y=exact_area, color='red', linestyle='--',
            linewidth=2.5, label=f'Точное значение ({exact_area:.4f})')
ax1.fill_between(wide['N'], exact_area - 0.01, exact_area + 0.01,
                 color='green', alpha=0.15, label='±0.01')

ax1.set_xlabel('Количество точек (N)', fontsize=13)
ax1.set_ylabel('Оценка площади', fontsize=13)
ax1.set_title('Зависимость оценки площади от N', fontsize=15, fontweight='bold')
ax1.legend(fontsize=11)
ax1.grid(True, alpha=0.3)

# === ПРАВЫЙ ГРАФИК (БЕЗ теоретической кривой) ===
# Просто данные, без маркеров
ax2.plot(wide['N'], wide['relative_error'],
         label='Широкая область', linewidth=1.5, alpha=0.7)
ax2.plot(narrow['N'], narrow['relative_error'],
         label='Узкая область', linewidth=1.5, alpha=0.7)

# Линия требуемой точности
ax2.axhline(y=0.01, color='green', linestyle=':', linewidth=2.5,
            label='Требуемая точность (1%)')

ax2.set_xlabel('Количество точек (N)', fontsize=13)
ax2.set_ylabel('Относительная ошибка', fontsize=13)
ax2.set_title('Зависимость относительной ошибки от N', fontsize=15, fontweight='bold')
ax2.set_yscale('log')
ax2.legend(fontsize=11)
ax2.grid(True, alpha=0.3, which='both')

plt.tight_layout()
plt.savefig('plots/combined_results.png', dpi=300, bbox_inches='tight')
print("График сохранён!")
plt.show()