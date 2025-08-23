class SortingVisualizer {
    constructor() {
        this.array = [];
        this.steps = [];
        this.currentStep = 0;
        this.isRunning = false;
        this.comparisons = 0;
        this.swaps = 0;
        this.startTime = 0;
        this.speed = 5;
        this.animationId = null;
        
        this.initializeEventListeners();
        this.generateArray();
    }

    initializeEventListeners() {
        document.getElementById('generateBtn').addEventListener('click', () => this.generateArray());
        document.getElementById('sortBtn').addEventListener('click', () => this.startSorting());
        document.getElementById('resetBtn').addEventListener('click', () => this.reset());
        document.getElementById('stepBtn').addEventListener('click', () => this.step());
        document.getElementById('arraySize').addEventListener('change', () => this.generateArray());
        document.getElementById('speed').addEventListener('input', (e) => {
            this.speed = parseInt(e.target.value);
            document.getElementById('speedValue').textContent = this.speed;
        });
    }

    generateArray() {
        const size = parseInt(document.getElementById('arraySize').value);
        this.array = [];
        for (let i = 0; i < size; i++) {
            this.array.push(Math.floor(Math.random() * 100) + 1);
        }
        this.reset();
        this.renderArray();
    }

    reset() {
        if (this.animationId) {
            clearTimeout(this.animationId);
            this.animationId = null;
        }
        this.steps = [];
        this.currentStep = 0;
        this.isRunning = false;
        this.comparisons = 0;
        this.swaps = 0;
        this.updateInfo();
        this.renderArray();
    }

    startSorting() {
        if (this.isRunning) return;
        
        this.isRunning = true;
        this.startTime = Date.now();
        this.comparisons = 0;
        this.swaps = 0;
        
        const algorithm = document.getElementById('algorithm').value;
        this.steps = [];
        this.currentStep = 0;
        
        // Store initial state
        this.steps.push([...this.array]);
        
        try {
            switch (algorithm) {
                case 'bubble':
                    this.bubbleSort();
                    break;
                case 'quick':
                    this.quickSort();
                    break;
                case 'merge':
                    this.mergeSort();
                    break;
                case 'insertion':
                    this.insertionSort();
                    break;
                case 'selection':
                    this.selectionSort();
                    break;
                default:
                    throw new Error(`Unknown algorithm: ${algorithm}`);
            }
            
            this.animateSteps();
        } catch (error) {
            console.error('Sorting error:', error);
            this.isRunning = false;
            this.updateInfo();
        }
    }

    bubbleSort() {
        const arr = [...this.array];
        const n = arr.length;
        
        for (let i = 0; i < n - 1; i++) {
            for (let j = 0; j < n - i - 1; j++) {
                this.comparisons++;
                if (arr[j] > arr[j + 1]) {
                    [arr[j], arr[j + 1]] = [arr[j + 1], arr[j]];
                    this.swaps++;
                    this.steps.push([...arr]);
                }
            }
        }
    }

    quickSort() {
        const arr = [...this.array];
        this.quickSortHelper(arr, 0, arr.length - 1);
    }

    quickSortHelper(arr, low, high) {
        if (low < high) {
            const pi = this.partition(arr, low, high);
            this.quickSortHelper(arr, low, pi - 1);
            this.quickSortHelper(arr, pi + 1, high);
        }
    }

    partition(arr, low, high) {
        const pivot = arr[high];
        let i = low - 1;
        
        for (let j = low; j < high; j++) {
            this.comparisons++;
            if (arr[j] < pivot) {
                i++;
                [arr[i], arr[j]] = [arr[j], arr[i]];
                this.swaps++;
                this.steps.push([...arr]);
            }
        }
        [arr[i + 1], arr[high]] = [arr[high], arr[i + 1]];
        this.swaps++;
        this.steps.push([...arr]);
        return i + 1;
    }

    mergeSort() {
        const arr = [...this.array];
        this.mergeSortHelper(arr, 0, arr.length - 1);
    }

    mergeSortHelper(arr, left, right) {
        if (left < right) {
            const mid = Math.floor((left + right) / 2);
            this.mergeSortHelper(arr, left, mid);
            this.mergeSortHelper(arr, mid + 1, right);
            this.merge(arr, left, mid, right);
        }
    }

    merge(arr, left, mid, right) {
        const leftArr = arr.slice(left, mid + 1);
        const rightArr = arr.slice(mid + 1, right + 1);
        
        let i = 0, j = 0, k = left;
        
        while (i < leftArr.length && j < rightArr.length) {
            this.comparisons++;
            if (leftArr[i] <= rightArr[j]) {
                arr[k] = leftArr[i];
                i++;
            } else {
                arr[k] = rightArr[j];
                j++;
            }
            k++;
            this.steps.push([...arr]);
        }
        
        while (i < leftArr.length) {
            arr[k] = leftArr[i];
            i++;
            k++;
            this.steps.push([...arr]);
        }
        
        while (j < rightArr.length) {
            arr[k] = rightArr[j];
            j++;
            k++;
            this.steps.push([...arr]);
        }
    }

    insertionSort() {
        const arr = [...this.array];
        const n = arr.length;
        
        for (let i = 1; i < n; i++) {
            const key = arr[i];
            let j = i - 1;
            
            while (j >= 0 && arr[j] > key) {
                this.comparisons++;
                arr[j + 1] = arr[j];
                j--;
                this.steps.push([...arr]);
            }
            arr[j + 1] = key;
            this.steps.push([...arr]);
        }
    }

    selectionSort() {
        const arr = [...this.array];
        const n = arr.length;
        
        for (let i = 0; i < n - 1; i++) {
            let minIdx = i;
            for (let j = i + 1; j < n; j++) {
                this.comparisons++;
                if (arr[j] < arr[minIdx]) {
                    minIdx = j;
                }
            }
            if (minIdx !== i) {
                [arr[i], arr[minIdx]] = [arr[minIdx], arr[i]];
                this.swaps++;
                this.steps.push([...arr]);
            }
        }
    }

    animateSteps() {
        if (this.currentStep >= this.steps.length) {
            this.isRunning = false;
            this.updateInfo();
            return;
        }
        
        this.array = [...this.steps[this.currentStep]];
        this.renderArray();
        this.updateInfo();
        
        this.currentStep++;
        
        const delay = (11 - this.speed) * 100; // Convert speed to delay
        this.animationId = setTimeout(() => this.animateSteps(), delay);
    }

    step() {
        if (this.isRunning) return; // Don't allow stepping while animating
        
        if (this.currentStep >= this.steps.length) {
            // If no steps available, generate them
            if (this.steps.length === 0) {
                this.generateSteps();
            } else {
                return; // Already at the end
            }
        }
        
        this.array = [...this.steps[this.currentStep]];
        this.renderArray();
        this.updateInfo();
        this.currentStep++;
    }

    generateSteps() {
        const algorithm = document.getElementById('algorithm').value;
        this.steps = [];
        this.currentStep = 0;
        this.comparisons = 0;
        this.swaps = 0;
        
        // Store initial state
        this.steps.push([...this.array]);
        
        switch (algorithm) {
            case 'bubble':
                this.bubbleSort();
                break;
            case 'quick':
                this.quickSort();
                break;
            case 'merge':
                this.mergeSort();
                break;
            case 'insertion':
                this.insertionSort();
                break;
            case 'selection':
                this.selectionSort();
                break;
        }
    }

    renderArray() {
        const container = document.getElementById('arrayContainer');
        container.innerHTML = '';
        
        const maxValue = Math.max(...this.array);
        
        this.array.forEach((value, index) => {
            const bar = document.createElement('div');
            bar.className = 'bar';
            bar.style.height = `${(value / maxValue) * 250}px`;
            bar.textContent = value;
            
            // Add visual effects based on sorting state
            if (this.isRunning && this.currentStep < this.steps.length) {
                const currentStepArray = this.steps[this.currentStep];
                if (currentStepArray && currentStepArray[index] !== this.array[index]) {
                    bar.classList.add('swapping');
                }
            }
            
            // Check if this element is in its final sorted position
            if (this.isSortedUpTo(index)) {
                bar.classList.add('sorted');
            }
            
            container.appendChild(bar);
        });
    }

    isSortedUpTo(index) {
        if (index === 0) return true;
        return this.array[index] >= this.array[index - 1];
    }

    updateInfo() {
        document.getElementById('comparisons').textContent = this.comparisons;
        document.getElementById('swaps').textContent = this.swaps;
        
        const elapsed = this.isRunning ? Date.now() - this.startTime : 0;
        document.getElementById('time').textContent = `${elapsed}ms`;
        
        let status = 'Ready';
        if (this.isRunning) {
            status = 'Sorting...';
        } else if (this.currentStep >= this.steps.length && this.steps.length > 0) {
            status = 'Complete';
        } else if (this.currentStep > 0) {
            status = `Step ${this.currentStep}/${this.steps.length}`;
        }
        
        document.getElementById('status').textContent = status;
    }
}

// Initialize the visualizer when the page loads
document.addEventListener('DOMContentLoaded', () => {
    new SortingVisualizer();
});